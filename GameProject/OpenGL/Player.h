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
class GoalLineRoot;
class GoalWarpHole;

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
	@fn �R���g���[���[���͏���
	@param	_KeyState �e���͋@��̓��͏��
	*/
	void InputController(const InputState& _KeyState);

	/*
	@fn �A�i���O�X�e�B�b�N���͏���
	@param	_KeyState �e���͋@��̓��͏��
	*/
	void InputStick(const InputState& _KeyState);

	/*
    @fn	�`�F�b�N�|�C���g�G�t�F�N�g�𐧌�
    */
	void CheckpointEffectControl();

	/*
    @fn		�v���C���[���q�b�g�������̏���
    @param	_HitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
    */
	void OnCollision(const GameObject& _HitObject)override;

	/*
	@fn	    �`�F�b�N�|�C���g�ɓ����������̏���
	@param	_HitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
	*/
	void HitCheckPoint(const GameObject& _HitObject);

	//�n�ʂ�Y���W
	const float MGroundYPos;

	//�����x
	const float MPlayerSpeedUp;

	//�v���C���[�̋������蔻��𐶐�
	SphereCollider* mSelfSphereCollider;
	//�v���C���[�̋������蔻��̑傫��
	Sphere mPlayerSphere;
	//�v���C���[�̍��ڂ���G�t�F�N�g
	SandEffectManager* mSandEffectManager;
	//�v���C���[�̃N���A�G�t�F�N�g
	ClearEffectManager* mClearEffectManager;
	//�v���C���[�̃f�X�G�t�F�N�g
	DeathEffectManager* mDeathEffectManager;
	//�v���C���[�̃`�F�b�N�|�C���g�G�t�F�N�g
	CheckpointEffectManager* mCheckpointEffectManager;
	//���ړ����̃|�C���^
	LateralMoveGround* mLateral;
	//�e�S�[�����C���̃|�C���^
	GoalLineRoot* mGoalLineRoot;
	//�S�[�����[�v�z�[���̃|�C���^
	GoalWarpHole* mGoalWarpHole;
	//���ړ����ɂ����������̑��x
	Vector3		  mLateralMoveVelocity;
	//�N���A��z�n�_
	Vector3       mClearPos;

	//���񂾂�
	bool		mDeathFlag;
	//�_���[�W���󂯂���
	bool		mDamageFlag;
	//���X�|�[����̑ҋ@�t���O
	bool		mStopFlag;		
	//�S�[�����o���邩
	bool        mGoalProductionFlag;
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
	//1�񂾂��e�S�[�����C���̃|�C���^���擾���邽�߂̃t���O
	bool        mGetGoalLineRootFlag;
	//1�񂾂��S�[�����[�v�z�[���̃|�C���^���擾���邽�߂̃t���O
	bool        mGetGoalWarpHoleFlag;

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
	//�S�[��z���W
	float       mGoalZPos;

public://�Q�b�^�[�Z�b�^�[

	bool GetGoalProductionFlag() { return mGoalProductionFlag; };
	bool GetClearFlag() { return mClearFlag; };
	bool GetDeathFlag() { return mDeathFlag; };
    bool GetEnableCheckpointFlag() { return mEnableCheckpointFlag; };
    int  GetLife() { return mLife; };

	/*
	@param _lateralMoveGroundPtr ���ړ����̃|�C���^
	*/
	void SetLateralMoveGroundPtr(LateralMoveGround* _lateralMoveGroundPtr) { mLateral = _lateralMoveGroundPtr; };
	/*
	@param	_goalLineRootPtr �e�S�[�����C���̃|�C���^
	*/
	void SetGoalLineRoot(GoalLineRoot* _goalLineRootPtr) { mGoalLineRoot = _goalLineRootPtr; };
	/*
	@param	_goalWarpHole �S�[�����[�v�z�[���̃|�C���^
	*/
	void SetGoalWarpHolePtr(GoalWarpHole* _goalWarpHole) { mGoalWarpHole = _goalWarpHole; };
};

