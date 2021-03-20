#pragma once
#include "ParticleEffectBase.h"

class DeathEffect :
	public ParticleEffectBase
{
public:
	DeathEffect(Vector3 _pos, Vector3 _vel, SceneBase::Scene _sceneTag, const Tag& _objectTag);
	~DeathEffect() {};

	void UpdateGameObject(float _deltaTime)override;
private:
};

