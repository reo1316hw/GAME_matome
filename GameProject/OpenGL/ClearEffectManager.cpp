/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
@param _playerPtr �v���C���[�̃|�C���^
*/
ClearEffectManager::ClearEffectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
	:GameObject(_SceneTag, _ObjectTag)
	, mAngle(0.0f)
	, mCreateTimingCount(0)
	, mCreateCount(0)
{
	mState = ParticleState::eParticleDisable;
	mSceneTag = _SceneTag;
	mTag = _ObjectTag;

	OneCreateClearFlag = true;

	mPlayer = _playerPtr;
}

/*
@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void ClearEffectManager::UpdateGameObject(float _deltaTime)
{
	if (mPlayer->GetClearFlag() && OneCreateClearFlag)
	{
		mState = ParticleState::eParticleActive;
	}
	else
	{
		mState = ParticleState::eParticleDisable;
	}

	switch (mState)
	{
	case ParticleState::eParticleDisable:
		break;
	case ParticleState::eParticleActive:

		//���q�̃N���A�G�t�F�N�g����
		CreateParticleClearEffect();
		
		//�g��̃N���A�G�t�F�N�g����
		CreateRippleClearEffect();

		break;
	}
}

/*
@fn ���q�̃N���A�G�t�F�N�g����
*/
void ClearEffectManager::CreateParticleClearEffect()
{
	//���x
	const float Speed = 30.0f;
	//1�t���[���ɔ������闱�q�̃N���A�G�t�F�N�g�̌�
	const int ParticleClearEffectNum = 4;

	mPosition = mPlayer->GetPosition();
	mPosition.z -= 200.0f;

	for (int i = 0; i < ParticleClearEffectNum; i++)
	{
		//���q�̃N���A�G�t�F�N�g�̃����_���Ȍ����x�N�g��
		Vector3 randVec = Vector3(rand() % 100 + 1.0f, rand() % 100 + 1.0f, rand() % 100 + 1.0f);

		randVec.Normalize();
		randVec.z *= -Speed;

		//�����̌�
		const int DirectionNum = 4;

		//��������ɗ��q�̃N���A�G�t�F�N�g���΂��悤�Ɍ��������肷��
		switch (i % DirectionNum)
		{
		case DirectionClearEffect::eLeftUnderClear:
			randVec.x *= -Speed;
			randVec.y *= -Speed;

			break;
		case DirectionClearEffect::eRightUpClear:
			randVec.x *= Speed;
			randVec.y *= Speed;
			break;
		case DirectionClearEffect::eLeftUpClear:
			randVec.x *= -Speed;
			randVec.y *= Speed;
			break;
		case DirectionClearEffect::eRightUnderClear:
			randVec.x *= Speed;
			randVec.y *= -Speed;
			break;
		}

		new ParticleClearEffect(mPosition, randVec, mTag, mSceneTag);
	}
}

/*
@fn �g��̃N���A�G�t�F�N�g����
*/
void ClearEffectManager::CreateRippleClearEffect()
{
	//��������^�C�~���O
	const int CreateTimingNum = 5;
	//��������ő��
	const int MaxCreateNum = 3;

	++mCreateTimingCount;

	if (mCreateTimingCount >= CreateTimingNum)
	{
		//���x�����߂�
		DecideVelocity();

		mRippleClearEffect = new RippleClearEffect(mPosition, mVelocity, mTag, mSceneTag);

		++mCreateCount;
		mCreateTimingCount = 0;
	}

	if (mCreateCount == MaxCreateNum)
	{
		OneCreateClearFlag = false;
	}
}

/*
@fn ���x�����߂�
*/
void ClearEffectManager::DecideVelocity()
{
	mVelocity = Vector3::sZERO;

	//����
	Vector3 direction = Vector3(0.0f, 0.0f, -1.0f);
	//���x
	float speed = 10.0f;

	mVelocity += direction * speed;
}