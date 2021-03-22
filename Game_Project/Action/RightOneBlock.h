#pragma once
#include "GameObject.h"

class RightOneBlock : public GameObject
{
public:
	RightOneBlock(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~RightOneBlock() {};

	void UpdateGameObject(float _deltaTime)override;
private:

	const float RIGHT_SPEED = 10.0f;
};