#pragma once
#include "GameObject.h"

class LateralMoveGround : public GameObject
{
public:
	LateralMoveGround(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const float _distance);
	~LateralMoveGround() {};

	static Vector3 GetVelocity() { return mSendVel; };

	void UpdateGameObject(float _deltaTime)override;
private:

	static Vector3 mSendVel;

	//”½“]ƒtƒ‰ƒO
	bool mReversFlag;
	
};