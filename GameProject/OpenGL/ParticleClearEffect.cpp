/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos ���q�̃N���A�G�t�F�N�g�̐����ꏊ
@param	_Vel ���q�̃N���A�G�t�F�N�g�̑��x
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
*/
ParticleClearEffect::ParticleClearEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:ParticleEffectBase(_Pos, _Vel, 30, "Assets/miniGlass.png", _SceneTag, _ObjectTag)
{
	mAlpha = 1.0f;
	mScale = 8.0f;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(Color::sWHITE);
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eParticleBlendAlpha);
	mSpeed = 1.3f;
}

/*
@fn		�N���A�G�t�F�N�g�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void ParticleClearEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	if (mLifeCount > 0)
	{
		if (mLifeCount <= 15)
		{
			mScale -= 4.0f;
			mVelocity *= mSpeed * -1.0f;
			mPosition += mVelocity;
		}
		else
		{
			mScale += 4.0f;
			mVelocity *= mSpeed;
			mPosition += mVelocity;
		}

		mParticle->SetScale(mScale);
		SetPosition(mPosition);
	}

	if (mLifeCount <= 0)
	{
		mParticle->SetVisible(false);
	}
}
