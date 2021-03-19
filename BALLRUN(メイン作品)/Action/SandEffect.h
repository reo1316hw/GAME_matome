#pragma once
#include "ParticleEffectBase.h"

class SandEffect :public ParticleEffectBase
{
public:
	SandEffect(Vector3 _pos,Vector3 _vel, SceneBase::Scene _sceneTag,const Tag& _objectTag);
	~SandEffect() {};

	void UpdateGameObject(float _deltaTime)override;
private:
	GameObject* owner;
	ParticleState state;
	Vector3 prePos;
	SceneBase::Scene sceneTag;
	Tag tag;
	int frameCount;
	int scene;
	float mAlpha;
	float mScale;
	float speed;
};

