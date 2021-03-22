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

	//リスポーンステートの値を格納する変数
	RespawnState		mRespawnState;

	//横移動床にあたった時の速度
	Vector3				mLateralMoveVelocity;

	// 重力
	const float GRAVITY_ACCEL = 2.0f;
	// 移動速度
	const float PLAYER_SPEED = 20.0f;
	// チュートリアル時の移動速度
	const float TUTORIAL_MOVE_SPEED = 13.0f;
	// 体力
	const int   PLAYER_LIFE = 3;

	static Vector3 mSendPos;

	static bool mSendDeathFlag;

	static bool mSendRespawnFlag;

	static bool mSendClearFlag;

	static int  mSendLife;

	// 死んだか
	bool		mDeathFlag;
	// ダメージを受けたか
	bool		mDamageFlag;
	// リスポーン後の待機フラグ
	bool		mStopFlag;
	// クリアしたか
	bool		mClearFlag;
	// ジャンプするか
	bool		mJumpFlag;
	// スケールを変えるか
	bool		mScaleFlag;

	int			mVisibleFrameCount;
	// 現在のシーンはどれか
	int			mScene;
	// 体力	
	int			mLife;
	// 角度
	float		mAngle;
	
	void OnCollision(const GameObject& _hitObject)override;
};

