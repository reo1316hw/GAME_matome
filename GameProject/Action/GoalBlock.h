#pragma once
#include "GameObject.h"

class GoalBlock : public GameObject
{
public:
	GoalBlock(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~GoalBlock() {};
private:
};