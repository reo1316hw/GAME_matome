#pragma once
#include "GameObject.h"

class MeshComponent;
class Mesh;
class BoxCollider;

class Ground : public GameObject
{
public:
	Ground(const Vector3& _pos, const Vector3& _size,const Tag& objectTag, const SceneBase::Scene _sceneTag);
	~Ground();

	void UpdateGameObject(float _deltaTime)override;
private:
	MeshComponent* meshComponent;
	BoxCollider* boxcollider;
	Mesh* mesh;
	//AABB groundBox;

	const float DOWN_SPEED = 10;

	void OnCollision(const GameObject& _hitObject)override;
};