/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �N���A�G�t�F�N�g�̐����ꏊ
@param	_Vel �N���A�G�t�F�N�g�̑��x
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
*/
ClearEffect::ClearEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:ParticleEffectBase(_Pos, _Vel, 30, "Assets/miniGlass.png", _SceneTag, _ObjectTag)
{
	mAlpha = 0.5f;
	mScale = 8.0f;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(Color::sYELLOW);
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eParticleBlendAlpha);
	mSpeed = 1.0f;
}

/*
@fn		�N���A�G�t�F�N�g�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void ClearEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	if (mLifeCount > 0)
	{
		mAlpha -= 0.01f;
		mScale += 1.0f;
		mParticle->SetAlpha(mAlpha);
		mParticle->SetScale(mScale);
		mVelocity = mVelocity * mSpeed;
		mPosition = mPosition + mVelocity;
		SetPosition(mPosition);
	}

	if (mLifeCount <= 0)
	{
		mParticle->SetVisible(false);
	}
}
