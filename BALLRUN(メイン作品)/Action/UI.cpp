#include "UI.h"
#include "Texture.h"
#include "Shader.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"

UI::UI(GameObject* _owner, int _drawOrder)
	:Component(_owner)
	, texture(nullptr)
	, drawOrder(_drawOrder)
	, textureWidth(0)
	, textureHeight(0)
	, visible(true)
{
	//レンダラーにポインターを送る
	RENDERER->AddUI(this);
}

UI::~UI()
{
	//レンダラーからポインタを削除する
	RENDERER->RemoveUI(this);
}

/*
@brief	描画処理
@param _shader 使用するシェーダークラスのポインタ
*/
void UI::Draw(Shader* _shader, const Vector2& _offset)
{
	//画像情報が空でないか、親オブジェクトが未更新状態でないか
	if (texture && owner->GetState() != State::Dead)
	{
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(textureWidth),
			static_cast<float>(textureHeight),
			1.0f);

		// スクリーン位置の平行移動
		Matrix4 transMat = Matrix4::CreateTranslation(
			Vector3(_offset.x - (textureWidth * 5.5f),
				(textureHeight * 5.0f) - _offset.y, 0.0f));

		Matrix4 world = scaleMatrix * transMat;

		_shader->SetMatrixUniform("uWorldTransform", world);

		texture->SetActive();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	}
}

/*
@fn テクスチャをセットし縦横の長さを計算する
@param _texture 使用するテクスチャのポインタ
*/
void UI::SetTexture(Texture* _texture)
{
	texture = _texture;
	textureWidth = texture->GetWidth();
	textureHeight = texture->GetHeight();
}
