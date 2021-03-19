#pragma once
#include "GameObject.h"

class VerticalBlock : public GameObject
{
public:
	VerticalBlock(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag);
	~VerticalBlock() {};
private:
};