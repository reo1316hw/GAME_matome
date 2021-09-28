/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �g��̃N���A�G�t�F�N�g�̐����ꏊ
@param	_Vel �g��̃N���A�G�t�F�N�g�̑��x
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
*/
RippleClearEffect::RippleClearEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:ParticleEffectBase(_Pos, _Vel, 50, "Assets/Texture/Effect/Ripple.png", _SceneTag, _ObjectTag)
{
	mAlpha = 1.0f;
	mScale = 0.0f;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(Color::sNAVY);
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eParticleBlendAlpha);
}

/*
@fn		�N���A�G�t�F�N�g�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void RippleClearEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	//���̈ʒu�ɖ߂��Ă����^�C�~���O
	const int TimingBackPos = 25;
	//�X�P�[���̕ϓ��l
	const float FluctuationScaleVal = 64.0f;

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
