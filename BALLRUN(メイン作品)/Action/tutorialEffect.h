#pragma once
#include "ParticleEffectBase.h"

class TutorialEffect : public ParticleEffectBase
{
public:
	TutorialEffect(const Vector3& _pos, const Vector3& _velocity, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~TutorialEffect() {};

	void UpdateGameObject(float _deltaTime)override;

private:
	GameObject* owner;
	float mScale;
	float mAlpha;
};

