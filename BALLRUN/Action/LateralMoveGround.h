#pragma once
#include "GameObject.h"

class LateralMoveGround : public GameObject
{
public:
	LateralMoveGround(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag, const float _distance);
	~LateralMoveGround() {};

	static Vector3 GetVelocity() { return sendVel; };

	void UpdateGameObject(float _deltaTime)override;
private:

	static Vector3 sendVel;

	//”½“]ƒtƒ‰ƒO
	bool reversFlag;
	
};