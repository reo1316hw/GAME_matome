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
	:ParticleEffectBase(_Pos, _Vel, 60, "Assets/Texture/Effect/Particle.png", _SceneTag, _ObjectTag)
{
	mAlpha = 1.0f;
	mScale = 0.0f;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(Color::sWHITE);
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eParticleBlendAdd);
}

/*
@fn		�N���A�G�t�F�N�g�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void ParticleClearEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	//���̈ʒu�ɖ߂��Ă����^�C�~���O
	const int TimingBackPos = 30;
	//�X�P�[���̕ϓ��l
	const float FluctuationScaleVal = 8.0f;

	if (mLifeCount <= TimingBackPos)
	{
		mScale -= FluctuationScaleVal;
		mPosition += mVelocity * -1.0f;
	}
	else
	{
		mScale += FluctuationScaleVal;
		mPosition += mVelocity;
	}

	mParticle->SetScale(mScale);
	SetPosition(mPosition);

	if (mLifeCount <= 0)
	{
		mParticle->SetVisible(false);
	}
}
