#pragma once
#include "GameObject.h"

class VerticalMoveGround : public GameObject
{
public:
	VerticalMoveGround(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~VerticalMoveGround() {};

	void UpdateGameObject(float _deltaTime)override;
private:

	const float FORWARD_SPEED = 10.0f;

	void OnCollision(const GameObject& _hitObject)override;
};
