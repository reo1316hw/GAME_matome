#pragma once
#include "GameObject.h"

class RightBlock : public GameObject
{
public:
	RightBlock(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~RightBlock() {};

	void UpdateGameObject(float _deltaTime)override;
private:

	Vector3 mInversionPos;
	//揺れるか
	bool mShakeFlag;
	//反転するか
	bool mReversFlag;

	//時間(進行度)
	float mElapseTime;
	//開始と終了の値の差分
	float mDifferencePos;
	//開始の値
	float mStart;
	//Tween(トゥイーン)の合計時間
	const float TOTAL_TIME = 1.0f;

	const float RIGHT_SPEED = 20.0f;
};