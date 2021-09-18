/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn	   �R���X�g���N�^
@param _FileName �摜�t�@�C���̖��O
*/
Sprite::Sprite(const std::string _FileName)
	:GameObject(SceneBase::Scene::eOtherScene, Tag::eOtherTag)
{
	mSpriteComponent = new SpriteComponent(this);

	mSpriteTexture = RENDERER->GetTexture(_FileName);
	mSpriteComponent->SetTexture(mSpriteTexture);
}
