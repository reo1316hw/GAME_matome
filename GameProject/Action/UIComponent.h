#pragma once

#include "Component.h"

class GameObject;
class Shader;
class Texture;
class Vector3;

/*
@file SpriteComponent.h
@brief 画像データクラスを管理し、スクリーン上に描画するクラス
*/
class UIComponent : public Component
{
public:
	/*
	@fn		コンストラクタ
	@param	アタッチするゲームオブジェクトのポインタ
	@param	_drawOrder 描画の順番（数値が小さいほど早く描画される）
	*/
	UIComponent(GameObject* _owner, int _drawOrder = 100);

	/*
	@fn		デストラクタ
	*/
	~UIComponent();

	/*
	@fn		描画処理
	@param _shader 使用するシェーダークラスのポインタ
	*/
	virtual void Draw(Shader* _shader, const Vector3& _offset);
protected:
	//クラスのポインタ
	Texture* mTexture;
	//描画される順番（数値が少ないほど早く更新される）
	int mDrawOrder;
	//テクスチャの横幅
	int mTextureWidth;
	//テクスチャの縦幅
	int mTextureHeight;
	//描画を行うか
	bool mVisible;

	//UIのID、カウント用
	static int mUIid;
	//このUIのID
	int mMyUIid;

public://ゲッターセッター
	/*
	@return テクスチャの横幅
	*/
	int GetTexWidth() const { return mTextureWidth; }

	/*
	@return テクスチャの縦幅
	*/
	int GetTexHeight() const { return mTextureHeight; }

	/*
	@return 描画順
	*/
	int GetDrawOrder() { return mDrawOrder; }

	/*
	@fn		描画をするかどうかを取得する
	@return	true : 描画する , false : 描画しない
	*/
	bool GetVisible() const { return mVisible; }

	/*
	@return	UIのid
	*/
	int GetUIid() { return mMyUIid; }

	/*
	@fn		テクスチャをセットし縦横の長さを計算する
	@param	_texture 使用するテクスチャのポインタ
	*/
	virtual void SetTexture(Texture* _texture);

	/*
	@fn		描画をするかどうかを設定
	@param	true : 描画する , false : 描画しない
	*/
	void SetVisible(bool _visible) { mVisible = _visible; }
};

