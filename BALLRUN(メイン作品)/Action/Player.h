#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

class EffectManager;
class SphereCollider;
class LateralMoveGround;

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
	Player(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~Player();

	void UpdateGameObject(float _deltaTime)override;
	void GameObjectInput(const InputState& _keyState)override;

	static Vector3 GetPos()			{ return mSendPos; };
	static bool GetDeathFlag()		{ return mSendDeathFlag; };
	static bool GetRespawnFlag()	{ return mSendRespawnFlag; };
	static bool GetClearFlag()		{ return mSendClearFlag; };
	static int GetLife()			{ return mSendLife; };

	void SetDeathFlag(bool _deathFlag) { mSendDeathFlag = _deathFlag; };
	void SetClearFlag(bool _clearFlag) { mSendClearFlag = _clearFlag; };

private:
	SphereCollider*		mSelfSphereCollider;
	Sphere				mPlayerSphere;
	Vector3				mSandPos;
	ParticleState		mState;
	Vector3				mPrePos;
	SceneBase::Scene	mSceneTag;
	Tag					mSandTag;
	EffectManager*		mEffectManager;
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

	int			mVisibleFrameCount;
	// ���݂̃V�[���͂ǂꂩ
	int			mScene;
	// �̗�	
	int			mLife;
	// �p�x
	float		mAngle;
	
	void OnCollision(const GameObject& _hitObject)override;
};

