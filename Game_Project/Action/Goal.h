#pragma once
#include "ParticleEffectBase.h"

class Goal : public ParticleEffectBase
{
public:
	Goal(const Vector3& _pos, const Vector3& _velocity, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~Goal() {};

	void UpdateGameObject(float _deltaTime)override;

private:
};

