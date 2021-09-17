/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �C���N���[�h
*/
#include "ParticleEffectBase.h"

/*
@brief �O���錾
*/
class SandEffect;
class DeathEffect;
class ClearEffect;
class CheckpointEffect;
class Player;

class SandEffectManager : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_owner �Q�[���I�u�W�F�N�g�N���X�̃|�C���^
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	SandEffectManager(GameObject* _owner, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~SandEffectManager() {};

	/*
	@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;
	
private:

	//�Q�[���I�u�W�F�N�g�N���X�̃|�C���^
	GameObject*		 mOwner;
	//�p�[�e�B�N���̏��
	ParticleState	 mState;
	//�G�t�F�N�g�}�l�[�W���[�̍��W
	Vector3			 mPos;
	//�V�[���̃^�O
	SceneBase::Scene mSceneTag;
	//�A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	Tag				 mTag;
	//���ڂ���G�t�F�N�g
	SandEffect*		 mSandEffect;

	//�C�ӂ̃^�C�~���O�ō��ڂ���G�t�F�N�g�𐶐����邽�߂̃J�E���g
	int				 mCreateSandEffectCount;
};

