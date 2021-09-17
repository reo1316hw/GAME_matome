/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn	�R���X�g���N�^
*/
MainCameraObject::MainCameraObject() 
	: GameObject(SceneBase::other,Tag::Camera,true)
{
	mInitPos = Vector3(0.0f, 0.0f, -100000.0f);
	SetPosition(mInitPos);
	mTag = Tag::Camera;
}

/*
@fn	�f�X�g���N�^
*/
MainCameraObject::~MainCameraObject()
{
}

/*
@fn		���̃N���X�̓|�[�Y���ɕʃN���X����X�V�֐����Ă΂�邱�Ƃ�����
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void MainCameraObject::UpdateGameObject(float _deltaTime)
{
	mPosition = mOffsetPos + mLerpObject;

	SetPosition(mPosition);
	Matrix4 view = Matrix4::CreateLookAt(mPosition, mLerpObject, Vector3::sUNIT_Y);
	RENDERER->SetViewMatrix(view);
}

/*
@param _Offset�@���������W�Ƃ̍�
@param _parentPos�@������W
*/
void MainCameraObject::SetViewMatrixLerpObject(const Vector3 & _Offset, const Vector3 & _ParentPos)
{
	mHasParentObject = true;
	mOffsetPos = _Offset;
	mLerpObject = _ParentPos;
}
