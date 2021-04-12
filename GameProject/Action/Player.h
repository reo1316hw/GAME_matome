/*
@brief	�v���v���Z�b�T
*/
#pragma once

/*
@brief	�C���N���[�h
*/
#include "GameObject.h"
#include "ParticleEffectBase.h"

class EffectManager;
class SphereCollider;
class LateralMoveGround;

/*
@enum	�v���C���[�̃��X�|�[���X�e�[�g
@brief	�ǂ̃��X�|�[���n�_�ŕ������邩
*/
enum class RespawnState
{
	respawnNone = 0,
	respawnComplete01 = 1,
	respawnComplete02 = 2,
	respawnComplete03 = 3
};

class Player:public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_pos �v���C���[�̍��W
	@param	_size �v���C���[�̃T�C�Y
	@param	_objectTag �v���C���[�̃^�O
	@param	_sceneTag �V�[���̃^�O
	*/
	Player(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

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
	@param	_keyState �e���͋@��̓��͏��
	@brief	�L�[�{�[�h�A�}�E�X�A�R���g���[���[
	*/
	void GameObjectInput(const InputState& _keyState)override;

private:

	//�v���C���[�̋������蔻��𐶐�
	SphereCollider*		mSelfSphereCollider;
	//�v���C���[�̋������蔻��̑傫��
	Sphere				mPlayerSphere;
	//�v���C���[�̃G�t�F�N�g
	EffectManager*		mEffectManager;
	//���ړ����̃|�C���^
	LateralMoveGround*	mLateral;
	//���X�|�[���X�e�[�g�̒l���i�[����ϐ�
	RespawnState		mRespawnState;

	//���ړ����ɂ����������̑��x
	Vector3				mLateralMoveVelocity;

	// �d��
	const float GRAVITY_ACCEL = 2.0f;
	// �ړ����x
	const float PLAYER_SPEED = 20.0f;
	// �`���[�g���A�����̈ړ����x
	const float TUTORIAL_MOVE_SPEED = 13.0f;
	// �̗�
	const int   PLAYER_LIFE = 3;

	static Vector3 mSendPos;

	static bool mSendDeathFlag;

	static bool mSendRespawnFlag;

	static bool mSendClearFlag;

	static int  mSendLife;

	// ���񂾂�
	bool		mDeathFlag;
	// �_���[�W���󂯂���
	bool		mDamageFlag;
	// ���X�|�[����̑ҋ@�t���O
	bool		mStopFlag;
	// �N���A������
	bool		mClearFlag;
	// �W�����v���邩
	bool		mJumpFlag;
	// �X�P�[����ς��邩
	bool		mScaleFlag;

	//�v���C���[���_�ł��邽�߂̃J�E���g
	int			mVisibleFrameCount;
	// ���݂̃V�[���͂ǂꂩ
	int			mScene;
	// �̗�	
	int			mLife;

	// �p�x
	float		mAngle;
	
	/*
	@fn		�v���C���[���q�b�g�������̏���
	@param	_hitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
	*/
	void OnCollision(const GameObject& _hitObject)override;

public://�Q�b�^�[�Z�b�^�[

	static Vector3 GetPos() { return mSendPos; };
	static bool GetDeathFlag() { return mSendDeathFlag; };
	static bool GetRespawnFlag() { return mSendRespawnFlag; };
	static bool GetClearFlag() { return mSendClearFlag; };
	static int GetLife() { return mSendLife; };

	void SetDeathFlag(bool _deathFlag) { mSendDeathFlag = _deathFlag; };
	void SetClearFlag(bool _clearFlag) { mSendClearFlag = _clearFlag; };

};

