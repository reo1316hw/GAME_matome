/*
@brief インクルード
*/
#include "pch.h"

/*
@fn    コンストラクタ
@param _TopLeftOrigin 左上の原点
@param _playerPtr プレイヤーのポインタ
*/
GoalLineRoot::GoalLineRoot(const Vector3& _TopLeftOrigin, Player* _playerPtr)
: mGoalLine(nullptr)
, mTextureName("0")
, mPos(_TopLeftOrigin)
, mVel(Vector3::sZERO)
{
	//ゴールライン生成
	for (int i = 0; i < 22; i++)
	{
		mPos = _TopLeftOrigin;

		//各ゴールラインの速度を指定
		SpecifyVel(i);
		//各ゴールラインの座標を指定
		SpecifyPos(i);
		//各ゴールラインのテクスチャデータを指定
		SpecifyTextureName(i);

		mGoalLine = new GoalLine(mPos, mVel, mTextureName, Tag::eOtherTag, SceneBase::Scene::eTutorial, _playerPtr);
	}
}

GoalLineRoot::~GoalLineRoot()
{
	delete mGoalLine;
}

/*
@fn    各ゴールラインの速度を指定
@param _Quantity 個数
*/
void GoalLineRoot::SpecifyVel(const int _Quantity)
{
	//左側(中心含む)に配置されているゴールラインの速度指定
	if (_Quantity < 12)
	{
		mVel.y = 2.0f + (0.1f * _Quantity);
	}
	//右側(中心含まない)に配置されているゴールラインの速度指定
	else
	{
		mVel.y = 4.0f - (0.1f * _Quantity);
	}
}

/*
@fn    各ゴールラインの座標を指定
@param _Quantity 個数
*/
void GoalLineRoot::SpecifyPos(const int _Quantity)
{
	//上段の座標指定
	if (_Quantity % 2 == 0)
	{
		mPos.x += _Quantity * 50.0f;
	}
	//下段の座標指定
	else if (_Quantity % 2 == 1)
	{
		mPos.x += _Quantity * 50.0f - 50.0f;
		mPos.y -= 100.0f;

		//各ゴールラインの速度を補正
		CorrectVel(_Quantity);
	}
}

/*
@fn    各ゴールラインの速度を補正
@param _Quantity 個数
*/
void GoalLineRoot::CorrectVel(const int _Quantity)
{
	//下段と上段で速度を同じにするために補正
	if (_Quantity < 12)
	{
		mVel.y -= 0.1f;
	}
	else
	{
		mVel.y += 0.1f;
	}
}

/*
@fn   各ゴールラインのテクスチャデータを指定
@param _Quantity 個数
*/
void GoalLineRoot::SpecifyTextureName(const int _Quantity)
{
	switch (_Quantity % 4)
	{
	case 0:
		mTextureName = "Assets/heart.png";
		break;
	case 1:
		mTextureName = "Assets/checkpoint_stage01.png";
		break;
	case 2:
		mTextureName = "Assets/checkpoint_stage01.png";
		break;
	case 3:
		mTextureName = "Assets/heart.png";
		break;
	}
}
