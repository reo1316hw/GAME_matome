#pragma once
#include "GameObject.h"

class RightOneBlock_02 : public GameObject
{
public:
	RightOneBlock_02(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag);
	~RightOneBlock_02() {};

	void UpdateGameObject(float _deltaTime)override;
private:
	//Å@à⁄ìÆêÊ
	Vector3 tmpPos;

	const float RIGHT_SPEED = 10;
};