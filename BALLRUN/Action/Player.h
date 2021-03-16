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
	Player(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag);
	~Player();

	void UpdateGameObject(float _deltaTime)override;
	void GameObjectInput(const InputState& _keyState)override;

	static Vector3 GetPos() { return sendPos; };
	static bool GetDeathFlag() { return sendDeathFlag; };
	static bool GetRespawnFlag() { return sendRespawnFlag; };
	static bool GetClearFlag() { return sendClearFlag; };
	static int GetLife() { return sendLife; };

	void SetDeathFlag(bool _deathFlag) { sendDeathFlag = _deathFlag; };
	void SetClearFlag(bool _clearFlag) { sendClearFlag = _clearFlag; };

private:
	SphereCollider* selfSphereCollider;
	Sphere playerSphere;
	Vector3 sandPos;
	ParticleState state;
	Vector3 prePos;
	SceneBase::Scene sceneTag;
	Tag sandTag;
	EffectManager* effectManager;
	LateralMoveGround* lateral;

	//リスポーンステートの値を格納する変数
	RespawnState respawnState;

	Vector3 moveVelocity;
	Vector3 JumpPos;

	// 重力
	const float GRAVITY_ACCEL = 2.0f;
	// 移動速度
	const float PLAYER_SPEED = 20.0f;
	// チュートリアル時の移動速度
	const float TUTORIAL_MOVE_SPEED = 13.0f;
	// 体力
	const int   PLAYER_LIFE = 3;

	static Vector3 sendPos;

	static bool sendDeathFlag;

	static bool sendRespawnFlag;

	static bool sendClearFlag;

	static int sendLife;

	// 死んだか
	bool		deathFlag;
	// ダメージを受けたか
	bool		damageFlag;
	// リスポーン後の待機フラグ
	bool		stopFlag;
	// クリアしたか
	bool		clearFlag;
	// ジャンプするか
	bool		jumpFlag;
	// スケールを変えるか
	bool		scaleFlag;

	int frameCount;
	// 現在のシーンはどれか
	int			scene;
	// 体力	
	int			life;
	// 角度
	float		angle;
	
	void OnCollision(const GameObject& _hitObject)override;
};

