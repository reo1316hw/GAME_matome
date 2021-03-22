#pragma once
#include "GameObject.h"

class Ground : public GameObject
{
public:
	Ground(const Vector3& _pos, const Vector3& _size,const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~Ground() {};
private:
	const float DOWN_SPEED = 10;
};