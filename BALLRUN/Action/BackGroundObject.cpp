#include "BackGroundObject.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "MainCameraObject.h"
#include "ColliderComponent.h"

/*
@param _pos ���W
@param _size �T�C�Y
@param _fileName ���b�V���f�[�^�̃A�h���X
*/
BackGroundObject::BackGroundObject(const Vector3 & _pos, const Vector3 & _size, const std::string & _fileName)
{
	SetPosition(_pos);
	SetScale(_size);
	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Stage/" + _fileName + ".gpmesh"));
	ColliderComponent* col = new ColliderComponent(this, 100, Vector3(1, 1, 1), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
}

BackGroundObject::~BackGroundObject()
{
}

void BackGroundObject::UpdateGameObject(float deltaTime)
{
}
