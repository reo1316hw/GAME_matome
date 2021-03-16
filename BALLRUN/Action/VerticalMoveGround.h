#pragma once
#include "GameObject.h"

class VerticalMoveGround : public GameObject
{
public:
	VerticalMoveGround(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag);
	~VerticalMoveGround() {};

	void UpdateGameObject(float _deltaTime)override;
private:
	//Å@à⁄ìÆêÊ
	Vector3 tmpPos;

	const float FORWARD_SPEED = 10;

	void OnCollision(const GameObject& _hitObject)override;
};
