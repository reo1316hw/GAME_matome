/*
@file  InvisibleMeshComponent.h
@brief アルファブレンドメッシュデータの管理と描画を行う
*/

/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class GameObject;
class Mesh;

class InvisibleMeshComponent : public Component
{
public:

	/*
	@fn		コンストラクタ
	@param	_owner アタッチするゲームオブジェクトのポインタ
	@param	_skelton スケルトンデータを用いるか。
	@sa		SkeletalMeshComponent.h
	*/
	InvisibleMeshComponent(GameObject* _owner, bool _skelton = false);

	/*
	@fn	デストラクタ
	*/
	~InvisibleMeshComponent();

	/*
	@fn		描画処理
	@param	_shader 使用するシェーダークラスのポインタ
	*/
	virtual void Draw(class Shader* _shader);

protected:

	/*
	@fn		テクスチャをステージごとにセット
	@brief	ディフューズマップ	stage00
			法線マップ			stage01
			スペキュラーマップ	stage02
			自己放射マップ		stage03
	@param	_shader 使用するシェーダークラスのポインタ
	*/
	virtual void SetTextureToShader(class Shader* _shader);

	//メッシュデータクラスへのポインタ
	Mesh* mMesh;
	//テクスチャサイズ
	size_t mTextureIndex;
	//描画をするかどうか
	bool mVisible;
	//スケルトンデータを用いるか
	bool mSkeltonFlag;

public: //ゲッターセッター

	/*
	@return 設定されたMeshクラスのポインタ
	*/
	virtual Mesh* GetMesh() { return mMesh; }

	/*
	@fn		描画をするかどうかを取得する
	@return	true : 描画する , false : 描画しない(bool型)
	*/
	bool GetVisible() const { return mVisible; }

	/*
	@return スケルトンデータを用いるか(bool型)
	*/
	bool GetIsSkeltal()const { return mSkeltonFlag; }

	/*
	@fn		メッシュコンポーネントが使うMeshの設定
	@param	_mesh 設定するMeshクラスのポインタ
	*/
	virtual void SetMesh(Mesh* _mesh) { mMesh = _mesh; }

	/*
	@fn	メッシュコンポーネントが使うTextureインデックスの設定
	@param _index テクスチャサイズ
	*/
	void SetTextureIndex(size_t _index) { mTextureIndex = _index; }

	/*
	@fn		描画をするかどうかを設定
	@param	_visible true : 描画する , false : 描画しない
	*/
	void SetVisible(bool _visible) { mVisible = _visible; }
};

