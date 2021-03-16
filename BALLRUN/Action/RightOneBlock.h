#pragma once
#include "GameObject.h"

class RightOneBlock : public GameObject
{
public:
	RightOneBlock(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag);
	~RightOneBlock() {};

	void UpdateGameObject(float _deltaTime)override;
private:
	//Å@à⁄ìÆêÊ
	Vector3 tmpPos;

	const float RIGHT_SPEED = 10;
};