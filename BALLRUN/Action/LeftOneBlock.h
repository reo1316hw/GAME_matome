#pragma once
#include "GameObject.h"

class LeftOneBlock : public GameObject
{
public:
	LeftOneBlock(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag);
	~LeftOneBlock() {};

	void UpdateGameObject(float _deltaTime)override;
private:
	const float LEFT_SPEED = 10;
};