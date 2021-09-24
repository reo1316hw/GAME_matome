/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn	�R���X�g���N�^
*/
MainCameraObject::MainCameraObject() 
	: GameObject(SceneBase::Scene::eOtherScene,Tag::eCameraTag,true)
{
	mInitPos = Vector3(0.0f, 0.0f, -100000.0f);
	SetPosition(mInitPos);
	mTag = Tag::eCameraTag;
}

/*
@fn	�f�X�g���N�^
*/
MainCameraObject::~MainCameraObject()
{
}

/*
@fn		�J�����̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void MainCameraObject::UpdateGameObject(float _deltaTime)
{
	//���x�̒l
	const Vector3 VelocityValue = Vector3(0.0f, 5.0f, -10.0f);
	//�����x
	const float Acceleration = 1.5f;
	//���x
	Vector3 vel = Vector3::sZERO;

	//�N���A���ɃJ����������
	if (mPlayer != nullptr && mPlayer->GetClearFlag())
	{
		vel = VelocityValue;
		vel *= Acceleration;
		mOffsetPos += vel;
	}

	mPosition = mOffsetPos + mLerpObject;

	Matrix4 view = Matrix4::CreateLookAt(mPosition, mLerpObject, Vector3::sUNIT_Y);
	RENDERER->SetViewMatrix(view);

	SetPosition(mPosition);
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
