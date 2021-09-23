/*
@brief インクルード
*/
#include "pch.h"

/*
@fn    コンストラクタ
@param _TopLeftOrigin 左上の原点
@param	_SceneTag シーンのタグ
@param _playerPtr プレイヤーのポインタ
*/
GoalLineRoot::GoalLineRoot(const Vector3& _TopLeftOrigin, const SceneBase::Scene _SceneTag, Player* _playerPtr)
: mGoalLine(nullptr)
, mTextureName("0")
, mPos(_TopLeftOrigin)
, mVel(Vector3::sZERO)
, LeftNum(12)
{
	//ゴールラインのオブジェクト数
	const int GoalLineNum = 22;

	//ゴールライン生成
	for (int i = 0; i < GoalLineNum; i++)
	{
		mPos = _TopLeftOrigin;

		//各ゴールラインの速度を指定
		SpecifyVel(i);
		//各ゴールラインの座標を指定
		SpecifyPos(i);
		//各ゴールラインのテクスチャデータを指定
		SpecifyTextureName(i);

		mGoalLine = new GoalLine(mPos, mVel, mTextureName, Tag::eOtherTag, _SceneTag, _playerPtr);
	}
}

/*
@fn    各ゴールラインの速度を指定
@param _Quantity 個数
*/
void GoalLineRoot::SpecifyVel(const int _Quantity)
{
	//左側の初速度
	const float LeftInitialVelocity = 2.0f;
	//右側の初速度
	const float RightInitialVelocity = 4.0f;
	//各ゴールラインに追加する速度
	float addVel = 0.1f * _Quantity;
	//左側に配置されているゴールラインの速度
	float leftVel = 0.0f;
	//右側に配置されているゴールラインの速度
	float rightVel = 0.0f;

	//左側(中心含む)に配置されているゴールラインの速度指定
	if (_Quantity < LeftNum)
	{
		leftVel = LeftInitialVelocity + addVel;
		mVel.y = leftVel;
	}
	//右側(中心含まない)に配置されているゴールラインの速度指定
	else
	{
		rightVel = RightInitialVelocity - addVel;
		mVel.y = rightVel;
	}
}

/*
@fn    各ゴールラインの座標を指定
@param _Quantity 個数
*/
void GoalLineRoot::SpecifyPos(const int _Quantity)
{
	//列の数
	const int ColumnNum = 2;
	//各ゴールラインに追加する座標
	const float AddPos = 50.0f * _Quantity;
	//下段のX軸をずらす
	const float ShiftXPos = 50.0f;
	//下段のY軸をずらす
	const float ShiftYPos = 100.0f;

	//上段の座標指定
	if (_Quantity % ColumnNum == 0)
	{
		mPos.x += AddPos;
	}
	//下段の座標指定
	else if (_Quantity % ColumnNum == 1)
	{
		mPos.x += AddPos - ShiftXPos;
		mPos.y -= ShiftYPos;

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
	//補正値
	const float CorrectionValue = 0.1f;

	//下段と上段で速度を同じにするために補正
	if (_Quantity < LeftNum)
	{
		mVel.y -= CorrectionValue;
	}
	else
	{
		mVel.y += CorrectionValue;
	}
}

/*
@fn   各ゴールラインのテクスチャデータを指定
@param _Quantity 個数
*/
void GoalLineRoot::SpecifyTextureName(const int _Quantity)
{
	//1グループの中の数
	const int InGropeNum = 4;

	switch (_Quantity % InGropeNum)
	{
    //左上
	case 0:
		mTextureName = "Assets/heart.png";
		break;
	//左下
	case 1:
		mTextureName = "Assets/checkpoint_stage01.png";
		break;
	//右上
	case 2:
		mTextureName = "Assets/checkpoint_stage01.png";
		break;
    //右下
	case 3:
		mTextureName = "Assets/heart.png";
		break;
	}
}
