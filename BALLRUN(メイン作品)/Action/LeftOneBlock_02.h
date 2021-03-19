#pragma once
#include "GameObject.h"

class LeftOneBlock_02 : public GameObject
{
public:
	LeftOneBlock_02(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~LeftOneBlock_02() {};

	void UpdateGameObject(float _deltaTime)override;
private:

	const float LEFT_SPEED = 10;
};