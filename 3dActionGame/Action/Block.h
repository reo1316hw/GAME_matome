#pragma once
#include "GameObject.h"

class MeshComponent;
class Mesh;

class Block : public GameObject
{
public:
	Block(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag);
	~Block();

	void UpdateGameObject(float _deltaTime)override;
private:
	MeshComponent* meshComponent;
	Mesh* mesh;
};