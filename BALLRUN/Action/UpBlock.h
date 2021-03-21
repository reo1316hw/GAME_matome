#pragma once
#include "GameObject.h"

class UpBlock : public GameObject
{
public:
	UpBlock(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~UpBlock() {};

	void UpdateGameObject(float _deltaTime)override;
private:

	const float UP_SPEED = 10;
};