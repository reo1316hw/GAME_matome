/*
@brief	インクルード
*/
#include "Sprite.h"
#include "SceneBase.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "Texture.h"

/*
@fn		コンストラクタ
@param	_fileName 画像ファイルの名前
*/
Sprite::Sprite(const std::string _fileName)
	:GameObject(SceneBase::Scene::other, Tag::Other)
{
	mSpriteComponent = new SpriteComponent(this);

	mSpriteTexture = RENDERER->GetTexture(_fileName);
	mSpriteComponent->SetTexture(mSpriteTexture);
}
