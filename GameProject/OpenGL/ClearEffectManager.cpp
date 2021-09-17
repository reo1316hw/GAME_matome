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
{
	mState = ParticleState::PARTICLE_DISABLE;
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

		//�N���A�G�t�F�N�g�̌�
		const int ClearEffectNum = 200;
		mPosition = mPlayer->GetPosition();

		for (int i = 0; i < ClearEffectNum; i++)
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
@param _Quantity ��
*/
void ClearEffectManager::DecideVelocity(const int _Quantity)
{
	//�����̌�
	const int DirectionNum = 5;
	//����
	float direction = 0.0f;
	//���x
	float speed = 0.0f;

	//���x��������
	mVelocity = Vector3::sZERO;
	speed = _Quantity * 0.1f;

	switch (_Quantity % DirectionNum)
	{
	case eLeftUpClear:
		direction = -0.6f;
		mVelocity.x = direction * speed;
		direction = 1.0f;
		mVelocity.y = direction * speed;
		break;
	case eLeftUpUpClear:
		direction = -0.3f;
		mVelocity.x = direction * speed;
		direction = 1.0f;
		mVelocity.y = direction * speed;
		break;
	case eUpClear:
		direction = 1.0f;
		mVelocity.y = direction * speed;
		break;
	case eRightUpUpClear:
		direction = 0.3f;
		mVelocity.x = direction * speed;
		direction = 1.0f;
		mVelocity.y = direction * speed;
		break;
	case eRightUpClear:
		direction = 0.6f;
		mVelocity.x = direction * speed;
		direction = 1.0f;
		mVelocity.y = direction * speed;
		break;
	}
}