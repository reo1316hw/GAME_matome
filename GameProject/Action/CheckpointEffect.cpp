/*
@brief	�C���N���[�h
*/
#include "CheckpointEffect.h"
#include "Renderer.h"
#include "ParticleComponent.h"
#include "SceneBase.h"
#include "GameObject.h"

/*
@fn		�R���X�g���N�^
@param	_pos �N���A�G�t�F�N�g�̐����ꏊ
@param	_vel �N���A�G�t�F�N�g�̑��x
@param	_objectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_sceneTag �V�[���̃^�O
*/
CheckpointEffect::CheckpointEffect(Vector3 _pos, Vector3 _vel, const Tag& _objectTag, SceneBase::Scene _sceneTag)
	:ParticleEffectBase(_pos, _vel, 30, "Assets/miniGlass.png", _sceneTag, _objectTag)
{
	mAlpha = 1.0f;
	mScale = 8.0f;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(Color::Yellow);
	mParticle->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM_ALPHA);
	mSpeed = 1.0f;
}

/*
@fn		�N���A�G�t�F�N�g�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void CheckpointEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	if (mLifeCount > 0)
	{
		mVelocity = mVelocity * mSpeed;
		mPosition = mPosition + mVelocity;

		SetPosition(mPosition);
	}

	if (mLifeCount <= 0)
	{
		mParticle->SetVisible(false);
	}
}
