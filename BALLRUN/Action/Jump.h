#pragma once
#include "GameObject.h"

class Jump : public GameObject
{
public:
	Jump(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~Jump() {};
private:
};