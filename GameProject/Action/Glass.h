#pragma once
#include "GameObject.h"

class InvisibleMeshComponent;

class Glass : public GameObject
{
public:
	Glass(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~Glass() {};

	void UpdateGameObject(float _deltaTime)override;
private:
	InvisibleMeshComponent* mInvisibleMeshComponent;

	//������܂ł̃J�E���g
	int mDownCount;

	// ������X�s�[�h
	const float DOWN_SPEED = 100.0f;

	void OnCollision(const GameObject& _hitObject)override;
};