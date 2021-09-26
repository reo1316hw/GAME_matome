/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �f�X�G�t�F�N�g�̐����ꏊ
@param	_Vel �N���A�G�t�F�N�g�̑��x
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
*/
DeathEffect::DeathEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:ParticleEffectBase(_Pos, _Vel, 40, "Assets/miniGlass.png", _SceneTag, _ObjectTag)
{
	mAlpha = 1.0f;
	mScale = 16.0f;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(Color::sWHITE);
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eParticleBlendAlpha);
	mVelocity = _Vel;
	mSpeed = 1.15f;
}

/*
@fn		�f�X�G�t�F�N�g�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void DeathEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	//�A���t�@�l�̍팸�l
	const float AlphaReductionVal = 0.01f;
	//�X�P�[���̒ǉ��l
	const float ScaleAddVal = 1.0f;

	if (mLifeCount > 0)
	{
		mAlpha -= AlphaReductionVal;
		mScale += ScaleAddVal;
		mVelocity = mVelocity * mSpeed;
		mPosition = mPosition + mVelocity;

		mParticle->SetAlpha(mAlpha);
		mParticle->SetScale(mScale);
		SetPosition(mPosition);
	}

	if (mLifeCount <= 0)
	{
		mParticle->SetVisible(false);
	}
}
