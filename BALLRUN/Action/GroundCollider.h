#pragma once
#include "GameObject.h"

class SphereCollider;

class GroundCollider : public GameObject
{
public:
	GroundCollider(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag);
	~GroundCollider();

	void UpdateGameObject(float _deltaTime)override;

private:
	SphereCollider* sphereCollider;
	Sphere groundSphere;
	GameObject* owner;
	SceneBase::Scene sceneTag;

	void OnCollision(const GameObject& _hitObject)override;

};

