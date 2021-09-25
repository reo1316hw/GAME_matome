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

		//�N���A�G�t�F�N�g�̌�
		const int ClearEffectNum = 360;
		mPosition = mPlayer->GetPosition();
		mPosition.z -= 200.0f;

		//�J���[�̌����l
		const Vector3 decColor = Vector3(0.002f, 0.002f, 0.0f);
		//�N���A�G�t�F�N�g�̃J���[�l
		Vector3 color = Color::sWHITE;

		for (int i = 0; i < ClearEffectNum; i++)
		{
			//���x�����߂�
			DecideVelocity();

			color -= decColor;

			mClearEffect = new ClearEffect(mPosition, mVelocity, color, mTag, mSceneTag);
		}

		OneCreateClearFlag = false;

		break;
	}
}

/*
@fn    ���x�����߂�
*/
void ClearEffectManager::DecideVelocity()
{
	//����
	Vector3 direction = Vector3(cosf(mAngle), sinf(mAngle), -0.3f);
	//���x
	Vector3 speed = Vector3(2.0f, 2.0f, 1.1f);

	mVelocity += direction * speed;
	mAngle += 0.1f;
}