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

	//���X�|�[���X�e�[�g�̒l���i�[����ϐ�
	RespawnState respawnState;

	Vector3 moveVelocity;
	Vector3 JumpPos;

	// �d��
	const float GRAVITY_ACCEL = 2.0f;
	// �ړ����x
	const float PLAYER_SPEED = 20.0f;
	// �`���[�g���A�����̈ړ����x
	const float TUTORIAL_MOVE_SPEED = 13.0f;
	// �̗�
	const int   PLAYER_LIFE = 3;

	static Vector3 sendPos;

	static bool sendDeathFlag;

	static bool sendRespawnFlag;

	static bool sendClearFlag;

	static int sendLife;

	// ���񂾂�
	bool		deathFlag;
	// �_���[�W���󂯂���
	bool		damageFlag;
	// ���X�|�[����̑ҋ@�t���O
	bool		stopFlag;
	// �N���A������
	bool		clearFlag;
	// �W�����v���邩
	bool		jumpFlag;
	// �X�P�[����ς��邩
	bool		scaleFlag;

	int frameCount;
	// ���݂̃V�[���͂ǂꂩ
	int			scene;
	// �̗�	
	int			life;
	// �p�x
	float		angle;
	
	void OnCollision(const GameObject& _hitObject)override;
};

