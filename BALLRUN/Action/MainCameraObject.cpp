#include "MainCameraObject.h"
#include "Renderer.h"
#include "ColliderComponent.h"


MainCameraObject::MainCameraObject() 
	: GameObject(SceneBase::other,Tag::Camera,true)
{
	SetPosition(Vector3(0,0,-110000));
	tag = Tag::Camera;
}

MainCameraObject::~MainCameraObject()
{
}

void MainCameraObject::UpdateGameObject(float _deltaTime)
{
	Vector3 pos = offsetPos + position;
	pos.x = lerpObject.x + offsetPos.x;
	pos.y = lerpObject.y + offsetPos.y;
	pos.z = lerpObject.z + offsetPos.z;
	position = pos;/*Vector3::Lerp(position, pos, _deltaTime * 6.0f);*/

	SetPosition(position);
	Matrix4 view = Matrix4::CreateLookAt(position, lerpObject, Vector3::UnitY);
	RENDERER->SetViewMatrix(view);
}

/*
@param _offset　見たい座標との差
@param _parentPos　見る座標
*/
void MainCameraObject::SetViewMatrixLerpObject(const Vector3 & _offset, const Vector3 & _parentPos)
{
	hasParentObject = true;
	offsetPos = _offset;
	lerpObject = _parentPos;
}
