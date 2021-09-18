/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn	   コンストラクタ
@param _FileName 画像ファイルの名前
*/
Sprite::Sprite(const std::string _FileName)
	:GameObject(SceneBase::Scene::eOtherScene, Tag::eOtherTag)
{
	mSpriteComponent = new SpriteComponent(this);

	mSpriteTexture = RENDERER->GetTexture(_FileName);
	mSpriteComponent->SetTexture(mSpriteTexture);
}
