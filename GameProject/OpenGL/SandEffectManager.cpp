/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_owner �Q�[���I�u�W�F�N�g�N���X�̃|�C���^
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
*/
SandEffectManager::SandEffectManager(GameObject* _owner, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:GameObject(_SceneTag, _ObjectTag)
{
	mOwner = _owner;
	mState = ParticleState::eParticleDisable;
	mPos = Vector3::sZERO;
	mSceneTag = _SceneTag;
	mTag = _ObjectTag;
}

/*
@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void SandEffectManager::UpdateGameObject(float _deltaTime)
{
	if (mPos != mOwner->GetPosition())
	{
		mState = ParticleState::eParticleActive;
	}
	else
	{
		mState = ParticleState::eParticleDisable;
	}

	Vector3 vel = Vector3::sZERO;

	switch (mState)
	{
	case ParticleState::eParticleDisable:
		break;
	case ParticleState::eParticleActive:

		//�|�W�V���������炷���߂̒萔
		const Vector3 ShittPos = Vector3(0.0f, 10.0f, 20.0f);
		//��������^�C�~���O
		const int CreateTiming = 6;

		mCreateSandEffectCount++;
		mPosition = mOwner->GetPosition();
		mPosition -= ShittPos;

		//6�t���[�����Ƃɐ�������
		if (mCreateSandEffectCount % CreateTiming == 0)
		{
			vel = Vector3(0.0f, 0.0f, -1.0);
			mSandEffect = new SandEffect(mPosition, vel, mSceneTag, mTag);
		}		

		break;
	}

	mPos = mOwner->GetPosition();
}
