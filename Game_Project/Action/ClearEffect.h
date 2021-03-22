#pragma once
#include "ParticleEffectBase.h"
class ClearEffect :
	public ParticleEffectBase
{
public:
	ClearEffect(Vector3 _pos, Vector3 _vel, SceneBase::Scene _sceneTag, const Tag& _objectTag);
	~ClearEffect() {};

	void UpdateGameObject(float _deltaTime)override;

private:
};

