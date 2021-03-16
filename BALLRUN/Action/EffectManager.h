#pragma once
#include "ParticleEffectBase.h"

class SandEffect;
class DeathEffect;
class ClearEffect;
class Player;

class EffectManager :
	public GameObject
{
public:
	EffectManager(GameObject* _owner, SceneBase::Scene _sceneTag , const Tag& _objectTag);
	~EffectManager() {};

	void UpdateGameObject(float _deltaTime)override;
	
private:
	GameObject* owner;
	ParticleState state;
	Vector3 prePos;
	SceneBase::Scene sceneTag;
	Tag tag;
	SandEffect* sandEffect;
	DeathEffect* deathEffect;
	ClearEffect* clearEffect;
	Player* player;

	int frameCount;
	int scene;

	// Šp“x
	float		angle;

	bool clearEffectFlag;
	bool deathEffectFlag;
};

