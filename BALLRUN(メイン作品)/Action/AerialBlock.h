#pragma once
#include "GameObject.h"

class AerialBlock : public GameObject
{
public:
	AerialBlock(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~AerialBlock() {};
private:
};