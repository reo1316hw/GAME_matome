/*
@brief インクルード
*/
#include "pch.h"

/*
@fn	コンストラクタ
*/
MainCameraObject::MainCameraObject() 
	: GameObject(SceneBase::Scene::eOtherScene,Tag::eCameraTag,true)
{
	mInitPos = Vector3(0.0f, 0.0f, -100000.0f);
	SetPosition(mInitPos);
	mTag = Tag::eCameraTag;
}

/*
@fn		カメラのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void MainCameraObject::UpdateGameObject(float _deltaTime)
{
	//速度の値
	const Vector3 VelocityValue = Vector3(0.0f, 6.0f, -8.0f);
	//速度
	Vector3 vel = Vector3::sZERO;

	//クリア時にカメラを引く
	if (mPlayer != nullptr && mPlayer->GetGoalProductionFlag())
	{
		vel = VelocityValue;
		mOffsetPos += vel;
	}

	mPosition = mOffsetPos + mLerpObject;

	Matrix4 view = Matrix4::CreateLookAt(mPosition, mLerpObject, Vector3::sUNIT_Y);
	RENDERER->SetViewMatrix(view);

	SetPosition(mPosition);
}

/*
@param _Offset　見たい座標との差
@param _parentPos　見る座標
*/
void MainCameraObject::SetViewMatrixLerpObject(const Vector3 & _Offset, const Vector3 & _ParentPos)
{
	mHasParentObject = true;
	mOffsetPos = _Offset;
	mLerpObject = _ParentPos;
}
