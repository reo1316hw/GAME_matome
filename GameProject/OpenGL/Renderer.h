/*
@file  Renderer.h
@brief 描画の進行を行うクラス
*/

/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief インクルード
*/
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"
#include "ParticleComponent.h"
#include "Player.h"

/*
@brief 前方宣言
*/
class SpriteComponent;
class Texture;
class Mesh;
class Game;
class MeshComponent;
class InvisibleMeshComponent;
class Shader;
class VertexArray;
class ParticleComponent;
class UIComponent;
class HeartUI;
class HDRRenderer;

#define RENDERER Renderer::GetInstance()

//平行光源用の構造体
struct DirectionalLight
{
	// 光の方向
	Vector3 m_direction;
	// 拡散反射色
	Vector3 m_diffuseColor;
	// 鏡面反射色
	Vector3 m_specColor;
};

/*
@enum テクスチャステージ
*/
enum class TextureStage
{
	eDiffuseMap,
	eNormalMap,
	eSpecularMap,
	eEmissiveMap,
	eShadowMap,
};

class Renderer
{
public:

	/*
	@fn	インスタンスを作成する
	*/
	static void CreateInstance();

	/*
	@fn	インスタンスを削除する
	*/
	static void DeleteInstance();

	/*
	@fn		初期化処理
	@return true : 成功 , false : 失敗(bool型)
	*/
	bool Initialize(float _screenWidth, float _screenHeight, bool _fullScreen);

	/*
	@fn	終了処理
	*/
	void Shutdown();

	/*
	@fn	ロードしたデータの解放
	*/
	void UnloadData();

	/*
	@fn	描画処理
	*/
	void Draw();
	   
	/*
	@fn		スプライトの追加
	@param	_spriteComponent　追加するSpriteComponentクラスのポインタ
	*/
	void AddSprite(SpriteComponent* _spriteComponent);

	/*
	@fn		スプライトの削除
	@param	_spriteComponent　削除するSpriteComponentクラスのポインタ
	*/
	void RemoveSprite(SpriteComponent* _spriteComponent);

	/*
	@fn		UIの追加
	@param	_ui　追加するUIクラスのポインタ
	*/
	void AddUI(UIComponent* _ui);

	/*
	@fn		UIの削除
	@param	_ui　削除するUIクラスのポインタ
	*/
	void RemoveUI(UIComponent* _ui);

	/*
	@fn		パーティクルの追加
	@param	_particleComponent　追加するParticleObjectクラスのポインタ
	*/
	void AddParticle(ParticleComponent* _particleComponent);

	/*
	@fn		パーティクルの削除
	@param	_particleComponent 削除するParticleObjectクラスのポインタ
	*/
	void RemoveParticle(ParticleComponent* _particleComponent);
	
	/*
	@fn		メッシュコンポーネントの追加
	@param	_meshComponent　追加するMeshComponentクラスのポインタ
	*/
	void AddMeshComponent(MeshComponent* _meshComponent);

	/*
	@fn		メッシュコンポーネントの削除
	@param	_meshComponent　削除するMeshComponentクラスのポインタ
	*/
	void RemoveMeshComponent(MeshComponent* _meshComponent);

	/*
	@fn		半透明メッシュコンポーネントの追加
	@param	_meshComponent　追加するMeshComponentクラスのポインタ
	*/
	void AddInvisibleMeshComponent(InvisibleMeshComponent* _invisibleMeshComponent);

	/*
	@fn		半透明メッシュコンポーネントの削除
	@param	_meshComponent　削除するMeshComponentクラスのポインタ
	*/
	void RemoveInvisibleMeshComponent(InvisibleMeshComponent* _invisibleMeshComponent);

private:

	//コンストラクタ、デストラクタの隠蔽
	Renderer();
	~Renderer();

	// スケルトンデータ
	std::unordered_map<std::string, class Skeleton*> mSkeletons;
	// アニメーションデータ
	std::unordered_map<std::string, class Animation*> mAnims;
	// スケルトンメッシュの描画に使われる
	std::vector<class SkeletalMeshComponent*>       mSkeletalMeshes;

	//自分のインスタンス
	static Renderer* mRenderer;
	//レンダラーの状態を含む構造体
	SDL_Renderer* mSdlRenderer;

	/*
	@fn		光源情報をシェーダーの変数にセットする
	@param  _shader セットするShaderクラスのポインタ
	@param	_View ビュー行列
	*/
	void SetLightUniforms(Shader* _shader, const Matrix4& _View);


	/*
	@fn		シェーダーの読み込み
	@return true : 成功 , false : 失敗(bool型)
	*/
	bool LoadShaders();

	/*
	@fn	Sprite用の頂点バッファとインデックスバッファの作成
	*/
	void CreateSpriteVerts();

	/*
	@fn	Particle用の頂点バッファとインデックスバッファの作成
	*/
	void CreateParticleVerts();

	/*
	@fn	Particleの描画
	*/
	void DrawParticle();

	/*
	@fn	Particleの描画
	@param	_framebuffer フレームバッファ
	@param	_View ビュー行列
	@param	_Proj 射影行列
	@param	_viewPortScale 表示領域スケール
	@param	_lit 光源情報をシェーダーの変数にセットするかのフラグ
	*/
	void Draw3DScene(unsigned int _framebuffer, const Matrix4& _View, const Matrix4& _Proj,
		float _viewPortScale = 1.0f, bool _lit = true);

	/*
	@fn		光源情報をシェーダーの変数にセットする
	@param  _blendType パーティクルに対するブレンドの種類
	*/
	void ChangeBlendMode(ParticleComponent::ParticleBlendType _blendType);

	/*
	@fn		テクスチャの変更
	@param	_changeTextureID 変更するテクスチャのid 
	*/
	void ChangeTexture(int _changeTextureID);

	/*
	@fn	ワールド空間のカメラ座標を計算
	*/
	Vector3 CalcCameraPos();

	//ファイル名でメッシュを取得するための連想配列
	std::unordered_map<std::string, Mesh*> mMeshes;
	//メッシュコンポーネントのポインタの可変長コンテナ
	std::vector<MeshComponent*> mMeshComponents;
	//インビジブルメッシュコンポーネントのポインタの可変長コンテナ
	std::vector<InvisibleMeshComponent*> mInvisibleMeshComponents;
	//スプライトコンポーネントのポインタの可変長コンテナ
	std::vector<SpriteComponent*> mSprites;
	//UIのポインタの可変長コンテナ
	std::vector<UIComponent*> mUis;
	//パーティクルのポインタ
	std::vector<ParticleComponent*> mParticles;
	//ファイル名でテクスチャを取得するための連想配列
	std::unordered_map<std::string, Texture*> mTextures;

	//クラスのポインタ
	//スプライト
	Shader* mSpriteShader;
	//スプライト用頂点
	VertexArray* mSpriteVerts;
	//UI
	Shader* mUiShader;
	//UI用頂点
	VertexArray* mUiVerts;
	//メッシュ
	Shader* mMeshShader;
	//スキンメッシュ
	class Shader*  mSkinnedShader;
	//インビジブルメッシュ
	Shader* mInvisibleMeshShader;
	Shader* mBasicShader;
	//パーティクル
	Shader* mParticleShader;
	//パーティクル用頂点
	VertexArray* mParticleVertex; 
	//プレイヤー
	Player* mPlayer;
	//HDRレンダラー
	HDRRenderer* mHDRRenderer;

	//ビュー行列
	Matrix4 mView;
	//射影行列
	Matrix4 mProjection;
	//ビルボード行列
	Matrix4 mBillboardMat;
	//スクリーンの横幅
	float mScreenWidth;
	//スクリーンの縦幅
	float mScreenHeight;
	//環境光
	Vector3 mAmbientLight;
	//平行光源
	DirectionalLight mDirLight;
	//ウィンドウ
	SDL_Window* mWindow;
	//コンテキスト
	SDL_GLContext mContext;
	// UIの初期座標に加算される座標
	Vector2 mAddPosition;
	//プレイヤーの体力UI
	HeartUI* mHeartUI;

	//未設定テクスチャの場合に割り当てられる黒色テクスチャ
	unsigned int mUndefineTexID;

public://ゲッターセッター

	/*
	@fn		インスタンスを取得する
	@return Rendererクラスのインスタンス(class Renderer)
	*/
	static Renderer* GetInstance() { return mRenderer; }

	/*
	@param	_FileName　取得したいテクスチャのファイル名
	@return Textureクラスのポインタ(class Texture)
	*/
	Texture* GetTexture(const std::string& _FileName);

	/*
	@param _FileName モデルへのアドレス
	@return スケルトンモデルの取得(class Skeleton)
	*/
	const class Skeleton* GetSkeleton(const char* _FileName);

	/*
	@param _FileName アニメーションへのアドレス
	@return スケルトンアニメーションの取得(class Animation)
	*/
	const class Animation* GetAnimation(const char* _FileName);

	/*
	@param	_FileName 取得したいメッシュのファイル名
	@return Meshクラスのポインタ(class Mesh)
	*/
	Mesh* GetMesh(const std::string& _FileName);

	/*
	@return	平行光源の構造体(struct DirectionalLight）
	*/
	DirectionalLight& GetDirectionalLight() { return mDirLight; }

	/*
	@return	スクリーンの横幅(float型)
	*/
	float GetScreenWidth() const { return mScreenWidth; }

	/*
	@return	スクリーンの縦幅(float型)
	*/
	float GetScreenHeight() const { return mScreenHeight; }

	/*
	@return	ビュー行列(class Matrix4)
	*/
	Matrix4 GetViewMatrix() const { return mView; };

	/*
	@return	射影行列(class Matrix4)
	*/
	Matrix4 GetProjectionMatrix() { return mProjection; }

	/*
	@return	射影行列(class Matrix4)
	*/
	SDL_Renderer* GetSDLRenderer() { return mSdlRenderer; }

	/*
	@return	未設定テクスチャの場合に割り当てられる黒色テクスチャ(unsigned int型)
	*/
	unsigned int GetUndefineTexID() { return mUndefineTexID; }

	/*
	@param	_View ビュー行列
	*/
	void SetViewMatrix(const Matrix4& _View) { mView = _View; }

	/*
	@param	_Ambient（環境光を表す）
	*/
	void SetAmbientLight(const Vector3& _Ambient) { mAmbientLight = _Ambient; }

	/*
	@fn	パーティクル用頂点を設定
	*/
	void SetParticleVertex();
};