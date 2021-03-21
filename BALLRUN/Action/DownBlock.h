#pragma once
#include "GameObject.h"

class DownBlock : public GameObject
{
public:
	DownBlock(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~DownBlock() {};

	void UpdateGameObject(float _deltaTime)override;
private:
	const float DOWN_SPEED = 20;
};