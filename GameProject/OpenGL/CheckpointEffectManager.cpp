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
CheckpointEffectManager::CheckpointEffectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
	:GameObject(_SceneTag, _ObjectTag)
{
	mState = ParticleState::PARTICLE_DISABLE;
	mSceneTag = _SceneTag;
	mTag = _ObjectTag;

	mPlayer = _playerPtr;
}

/*
@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void CheckpointEffectManager::UpdateGameObject(float _deltaTime)
{
	//�`�F�b�N�|�C���g��ʉ߂�����`�F�b�N�|�C���g�G�t�F�N�g���A�N�e�B�u�ɂ���
	if (mPlayer->GetEnableCheckpointFlag())
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
@param _Quantity ��
*/
void CheckpointEffectManager::DecideVelocity(const int _Quantity)
{
	//�����̌�
	const int DirectionNum = 8;
	//���x
	const float Speed = 10.0f;
	//����
	const float Direction = 1.0f;

	//���x��������
	mVelocity = Vector3::sZERO;

	//�e�����̑��x�ƌ������v�Z
	switch (_Quantity % DirectionNum)
	{
	case eRightCheckpoint:
		mVelocity.x = Direction * Speed;
		break;
	case eFrontCheckpoint:
		mVelocity.z = Direction * Speed;
		break;
	case eLeftCheckpoint:
		mVelocity.x = -Direction * Speed;
		break;
	case eBackCheckpoint:
		mVelocity.z = -Direction * Speed;
		break;
	case eRightFrontCheckpoint:
		mVelocity.x = Direction * Speed;
		mVelocity.z = Direction * Speed;
		break;
	case eLeftBackCheckpoint:
		mVelocity.x = -Direction * Speed;
		mVelocity.z = -Direction * Speed;
		break;
	case eRightBackCheckpoint:
		mVelocity.x = Direction * Speed;
		mVelocity.z = -Direction * Speed;
		break;
	case eLeftFrontCheckpoint:
		mVelocity.x = -Direction * Speed;
		mVelocity.z = Direction * Speed;
		break;
	}
}