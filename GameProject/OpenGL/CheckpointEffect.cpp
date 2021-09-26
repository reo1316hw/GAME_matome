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
CheckpointEffect::CheckpointEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:ParticleEffectBase(_Pos, _Vel, 60, "Assets/star.png", _SceneTag, _ObjectTag)
{
	mAlpha = 1.0f;
	mScale = 0.0f;
	mVelocity.y = 30.0f;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(Color::sYELLOW);
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eParticleBlendAlpha);
}

/*
@fn		�N���A�G�t�F�N�g�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void CheckpointEffect::UpdateGameObject(float _deltaTime)
{
	//�������Ԃ��J�E���g
	ParticleEffectBase::LifeCountDown();

	//���C�t�J�E���g��0���傫�������瑬�x�A�����x�A�X�P�[���̒l���X�V
	if (mLifeCount > 0)
	{
		//���x�̌����l
		const float VelocityMinusValue = 1.5f;
		//�X�P�[���̒ǉ��l
		const float ScaleAddVal = 4.0f;
		//�X�P�[���̍ő�l
		const float ScaleMaxVal = 64.0f;

		mPosition = mPosition + mVelocity;

		mVelocity.y -= VelocityMinusValue;
		
		if (mScale <= ScaleMaxVal)
		{
			mScale += ScaleAddVal;
		}

		mParticle->SetScale(mScale);
		SetPosition(mPosition);
	}

	//���C�t�J�E���g��0�ȉ��������猩���Ȃ�����
	if (mLifeCount <= 0)
	{
		mParticle->SetVisible(false);
	}
}