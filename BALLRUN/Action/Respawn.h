#pragma once
#include "GameObject.h"

class Respawn : public GameObject
{
public:
	Respawn(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag);
	~Respawn() {};
private:
};