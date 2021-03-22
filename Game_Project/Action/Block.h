#pragma once
#include "GameObject.h"

class Block : public GameObject
{
public:
	Block(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~Block() {};
private:
};