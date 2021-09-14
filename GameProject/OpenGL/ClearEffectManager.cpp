/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_objectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_sceneTag �V�[���̃^�O
@param _playerPtr �v���C���[�̃|�C���^
*/
ClearEffectManager::ClearEffectManager(const Tag& _objectTag, SceneBase::Scene _sceneTag, Player* _playerPtr)
	:GameObject(_sceneTag, _objectTag)
{
	mState = ParticleState::PARTICLE_DISABLE;
	mSceneTag = _sceneTag;
	mTag = _objectTag;

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
		mState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		mState = ParticleState::PARTICLE_DISABLE;
	}

	switch (mState)
	{
	case PARTICLE_DISABLE:
		break;
	case PARTICLE_ACTIVE:

		mPosition = mPlayer->GetPosition();

		for (int i = 0; i < 200; i++)
		{
			DecideVelocity(i);

			mClearEffect = new ClearEffect(mPosition, mVelocity, mTag, mSceneTag);
		}

		OneCreateClearFlag = false;

		break;
	}
}

/*
@fn    ���x�����߂�
@param _quantity ��
*/
void ClearEffectManager::DecideVelocity(const int _quantity)
{
	//����
	float direction = 0.0f;
	//���x
	float speed = 0.0f;

	mVelocity = Vector3(0.0f, 0.0f, 0.0f);
	speed = _quantity * 0.1f;

	switch (_quantity % 5)
	{
	case 0:
		direction = -0.6f;
		mVelocity.x = direction * speed;
		direction = 1.0f;
		mVelocity.y = direction * speed;
		break;
	case 1:
		direction = -0.3f;
		mVelocity.x = direction * speed;
		direction = 1.0f;
		mVelocity.y = direction * speed;
		break;
	case 2:
		direction = 1.0f;
		mVelocity.y = direction * speed;
		break;
	case 3:
		direction = 0.3f;
		mVelocity.x = direction * speed;
		direction = 1.0f;
		mVelocity.y = direction * speed;
		break;
	case 4:
		direction = 0.6f;
		mVelocity.x = direction * speed;
		direction = 1.0f;
		mVelocity.y = direction * speed;
		break;
	}
}