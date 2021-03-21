#pragma once
#include "GameObject.h"

class LeftBlock : public GameObject
{
public:
	LeftBlock(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~LeftBlock() {};

	void UpdateGameObject(float _deltaTime)override;
private:

	//反転する座標
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

	const float LEFT_SPEED = 20;
};