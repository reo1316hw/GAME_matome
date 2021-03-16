#pragma once

#include "Component.h"

class GameObject;
class Shader;
class Texture;
class Vector2;

/*
@file SpriteComponent.h
@brief 画像データクラスを管理し、スクリーン上に描画するクラス
*/
class UI : public Component
{
public:
	UI(GameObject* _owner, int _drawOrder = 100);
	~UI();

	/*
	@brief	描画処理
	@param _shader 使用するシェーダークラスのポインタ
	*/
	virtual void Draw(Shader* _shader, const Vector2& _offset);
protected:
	//クラスのポインタ
	Texture* texture;
	//描画される順番（数値が少ないほど早く更新される）
	int drawOrder;
	//テクスチャの横幅
	int textureWidth;
	//テクスチャの縦幅
	int textureHeight;
	//描画を行うか
	bool visible;
public://ゲッターセッター
	/*
	@fn テクスチャをセットし縦横の長さを計算する
	@param _texture 使用するテクスチャのポインタ
	*/
	virtual void SetTexture(Texture* _texture);

	/*
	@return テクスチャの横幅
	*/
	int GetTexWidth() const { return textureWidth; }

	/*
	@return テクスチャの縦幅
	*/
	int GetTexHeight() const { return textureHeight; }

	/*
	@return 描画順
	*/
	int GetDrawOrder() { return drawOrder; }

	/*
	@brief　描画をするかどうかを設定
	@param	true : 描画する , false : 描画しない
	*/
	void SetVisible(bool _visible) { visible = _visible; }

	/*
	@brief　描画をするかどうかを取得する
	@return	true : 描画する , false : 描画しない
	*/
	bool GetVisible() const { return visible; }
};

