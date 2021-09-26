/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos ���ڂ���̍��W
@param	_Vel ���ڂ���̑��x
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
*/
SandEffect::SandEffect(const Vector3 _Pos, const Vector3 _Vel, const SceneBase::Scene _SceneTag,const Tag& _ObjectTag)
	:ParticleEffectBase(_Pos,_Vel,30,"Assets/PhotonB.png", _SceneTag, _ObjectTag)
{
	const Vector3 Color = Vector3(0.95f, 0.95f, 0.95f);
	mAlpha = 0.5f;
	mScale = 32.0f;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(Color);
	mParticle->SetBlendMode(ParticleComponent::ParticleEnum::eParticleBlendAlpha);
}

/*
@fn		���ڂ���̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void SandEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	//�A���t�@�l�̍팸�l
	const float AlphaReductionVal = 0.01f;
	//�X�P�[���̒ǉ��l
	const float ScaleAddVal = 10.0f;

	if (mLifeCount > 0)
	{
		mAlpha -= AlphaReductionVal;
		mScale += ScaleAddVal;
		mPosition = mPosition + mVelocity;

		mParticle->SetAlpha(mAlpha);
		mParticle->SetScale(mScale);
		SetPosition(mPosition);
	}

	if (mLifeCount <=0)
	{
		mParticle->SetVisible(false);
	}
}
