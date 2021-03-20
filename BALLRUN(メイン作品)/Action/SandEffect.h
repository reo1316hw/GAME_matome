#pragma once
#include "ParticleEffectBase.h"

class SandEffect :public ParticleEffectBase
{
public:
	SandEffect(Vector3 _pos,Vector3 _vel, SceneBase::Scene _sceneTag,const Tag& _objectTag);
	~SandEffect() {};

	void UpdateGameObject(float _deltaTime)override;
private:
};

