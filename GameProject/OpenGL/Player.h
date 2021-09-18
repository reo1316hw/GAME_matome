/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �C���N���[�h
*/
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@brief �O���錾
*/
class SandEffectManager;
class ClearEffectManager;
class DeathEffectManager;
class CheckpointEffectManager;
class SphereCollider;
class LateralMoveGround;

/*
@brief �\����\��
*/
enum VisibleType
{
	eInvisible = 0,
	eVisible = 5
};

class Player:public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �v���C���[�̍��W
	@param	_Size �v���C���[�̃T�C�Y
	@param	_ObjectTag �v���C���[�̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	Player(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~Player() {};

	/*
	@fn		�v���C���[�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn		���͂������Ŏ󂯎��X�V�֐�
	@brief	��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
	@param	_KeyState �e���͋@��̓��͏��
	@brief	�L�[�{�[�h�A�}�E�X�A�R���g���[���[
	*/
	void GameObjectInput(const InputState& _KeyState)override;

private:

	/*
    @fn	�`�F�b�N�|�C���g�𐧌�
    */
	void CheckpointEffectControl();

	//�n�ʂ�Y���W
	const float MGroundYPos;

	//�v���C���[�̋������蔻��𐶐�
	SphereCollider*		mSelfSphereCollider;
	//�v���C���[�̋������蔻��̑傫��
	Sphere				mPlayerSphere;
	//�v���C���[�̍��ڂ���G�t�F�N�g
	SandEffectManager*  mSandEffectManager;
	//�v���C���[�̃N���A�G�t�F�N�g
	ClearEffectManager* mClearEffectManager;
	//�v���C���[�̃f�X�G�t�F�N�g
	DeathEffectManager* mDeathEffectManager;
	//�v���C���[�̃`�F�b�N�|�C���g�G�t�F�N�g
	CheckpointEffectManager* mCheckpointEffectManager;
	//���ړ����̃|�C���^
	LateralMoveGround*	mLateral;
	//���ړ����ɂ����������̑��x
	Vector3				mLateralMoveVelocity;

	//���񂾂�
	bool		mDeathFlag;
	//�_���[�W���󂯂���
	bool		mDamageFlag;
	//���X�|�[����̑ҋ@�t���O
	bool		mStopFlag;
	//�N���A������
	bool		mClearFlag;
	//�W�����v���邩
	bool		mJumpFlag;
	//�X�P�[����ς��邩
	bool		mScaleFlag;
	//�{�^�������͂��ꂽ��
	bool		mButtonFlag;
	//�ڒn������
	bool		mGroundFlag;
	//�����蔻����s����
	bool		mCollisionFlag;
	//�`�F�b�N�|�C���g��L���ɂ��邩
	bool		mEnableCheckpointFlag;
	//�`�F�b�N�|�C���g�{�[�h�ɓ���������
	bool		mHitCheckpointFlag;
	// ���X�|�[��������
	bool        mRespawnFlag;

	//�v���C���[���_�ł��邽�߂̃J�E���g
	int			mVisibleFrameCount;
	//���݂̃V�[���͂ǂꂩ
	int			mScene;
	//�̗�	
	int			mLife;
	//�`�F�b�N�|�C���g�G�t�F�N�g�𐶑�����
	int			mCheckpointEffectCount;
	//�p�x
	float		mAngle;
	
	/*
	@fn		�v���C���[���q�b�g�������̏���
	@param	_HitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
	*/
	void OnCollision(const GameObject& _HitObject)override;

public://�Q�b�^�[�Z�b�^�[

	bool GetClearFlag() { return mClearFlag; };
	bool GetDeathFlag() { return mDeathFlag; };
    bool GetEnableCheckpointFlag() { return mEnableCheckpointFlag; };
    int GetLife() { return mLife; };

};

