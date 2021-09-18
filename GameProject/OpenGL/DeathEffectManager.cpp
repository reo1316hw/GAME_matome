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
DeathEffectManager::DeathEffectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
	:GameObject(_SceneTag, _ObjectTag)
	, mRandVel(Vector3::sZERO)
{
	mState = ParticleState::eParticleDisable;
	mSceneTag = _SceneTag;
	mTag = _ObjectTag;

	mAngle = 0.0f;

	OneCreateDeathFlag = true;

	mPlayer = _playerPtr;
}

/*
@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void DeathEffectManager::UpdateGameObject(float _deltaTime)
{
	if (mPlayer->GetDeathFlag() && OneCreateDeathFlag == true)
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

		mCreateDeathEffectCount = 0;

		break;
	case ParticleState::eParticleActive:

		//�f�X�G�t�F�N�g�̌�
		const int DeathEffectNum = 50;

		mPosition = mPlayer->GetPosition();

		for (int i = 0; i < DeathEffectNum; i++)
		{
			DecideVelocity(i);

			mDeathEffect = new DeathEffect(mPosition, mRandVel, mTag, mSceneTag);
		}

		OneCreateDeathFlag = false;

		break;
	}
}

/*
@fn    ���x�����߂�
@param _Quantity ��
*/
void DeathEffectManager::DecideVelocity(const int _Quantity)
{
	//�����̌�
	const int DirectionNum = 3;
	//����
	const float Direction = 1.0f;

	mRandVel = Vector3(rand() % 100 + 1.0f, rand() % 100 + 1.0f, rand() % 100 + 1.0f);
	mRandVel.Normalize();

	switch (_Quantity % DirectionNum)
	{
	case eLeftDeath:
		mRandVel.x *= -Direction;
		break;
	case eBackDeath:
		mRandVel.z *= -Direction;
		break;
	case eLeftBackDeath:
		mRandVel.x *= -Direction;
		mRandVel.z *= -Direction;
		break;
	}
}
