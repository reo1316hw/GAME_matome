#pragma once
#include "GameObject.h"

class LeftBlock : public GameObject
{
public:
	LeftBlock(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag);
	~LeftBlock() {};

	void UpdateGameObject(float _deltaTime)override;
private:

	//反転する座標
	Vector3 inversionPos;

	//揺れるか
	bool shakeFlag;
	//反転するか
	bool reversFlag;

	//時間(進行度)
	float elapseTime;
	//開始と終了の値の差分
	float differencePos;
	//開始の値
	float start;
	//Tween(トゥイーン)の合計時間
	const float totalTime = 1.0f;

	const float LEFT_SPEED = 20;
};