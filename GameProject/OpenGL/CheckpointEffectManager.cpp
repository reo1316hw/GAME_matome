/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_objectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_sceneTag �V�[���̃^�O
@param _playerPtr �v���C���[�̃|�C���^
*/
CheckpointEffectManager::CheckpointEffectManager(const Tag& _objectTag, SceneBase::Scene _sceneTag, Player* _playerPtr)
	:GameObject(_sceneTag, _objectTag)
{
	mState = ParticleState::PARTICLE_DISABLE;
	mSceneTag = _sceneTag;
	mTag = _objectTag;

	mPlayer = _playerPtr;
}

/*
@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void CheckpointEffectManager::UpdateGameObject(float _deltaTime)
{
	//�`�F�b�N�|�C���g��ʉ߂�����`�F�b�N�|�C���g�G�t�F�N�g���A�N�e�B�u�ɂ���
	if (mPlayer->GetCheckpointFlag())
	{
		mState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		mState = ParticleState::PARTICLE_DISABLE;
	}

	//�`�F�b�N�|�C���g�̃X�e�[�g�𒲂ׂă`�F�b�N�|�C���g�G�t�F�N�g�̏������s��
	switch (mState)
	{
	//�A�N�e�B�u����Ȃ��Ȃ�
	case PARTICLE_DISABLE:
		break;
	//�A�N�e�B�u�Ȃ�
	case PARTICLE_ACTIVE:
		
		//�e�̃|�W�V�������擾
		mPosition = mPlayer->GetPosition();

		//8�����Ƀ`�F�b�N�|�C���g�G�t�F�N�g���΂�
		for (int i = 0; i < 8; i++)
		{
			// �`�F�b�N�|�C���g�G�t�F�N�g�̌��������߂�
			DecideVelocity(i);
			//�`�F�b�N�|�C���g�G�t�F�N�g�𐶐�
			mCheckpointEffect = new CheckpointEffect(mPosition, mVelocity, mTag, mSceneTag);
		}

		mState = ParticleState::PARTICLE_DISABLE;
		break;
	}
}

/*
@fn    ���x�����߂�
@param _quantity ��
*/
void CheckpointEffectManager::DecideVelocity(const int _quantity)
{
	//���x��������
	mVelocity = Vector3::Zero;

	//�e�����̑��x�ƌ������v�Z
	switch (_quantity % 8)
	{
	case 0:
		mVelocity.x = DIRECTION * SPEED;
		break;
	case 1:
		mVelocity.z = DIRECTION * SPEED;
		break;
	case 2:
		mVelocity.x = -DIRECTION * SPEED;
		break;
	case 3:
		mVelocity.z = -DIRECTION * SPEED;
		break;
	case 4:
		mVelocity.x = DIRECTION * SPEED;
		mVelocity.z = DIRECTION * SPEED;
		break;
	case 5:
		mVelocity.x = -DIRECTION * SPEED;
		mVelocity.z = -DIRECTION * SPEED;
		break;
	case 6:
		mVelocity.x = DIRECTION * SPEED;
		mVelocity.z = -DIRECTION * SPEED;
		break;
	case 7:
		mVelocity.x = -DIRECTION * SPEED;
		mVelocity.z = DIRECTION * SPEED;
		break;
	}
}