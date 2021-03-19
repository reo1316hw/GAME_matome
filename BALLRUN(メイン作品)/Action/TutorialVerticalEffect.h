#pragma once
#include "ParticleEffectBase.h"

class TutorialVerticalEffect : public ParticleEffectBase
{
public:
	TutorialVerticalEffect(const Vector3& _pos, const Vector3& _velocity, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~TutorialVerticalEffect() {};

	void UpdateGameObject(float _deltaTime)override;

private:
	GameObject* owner;
	float mScale;
	float mAlpha;
};

