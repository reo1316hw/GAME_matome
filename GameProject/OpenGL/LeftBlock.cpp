/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos 左移動床の座標
@param	_Size 左移動床のサイズ
@param	_ObjectTag 左移動床のタグ
@param	_SceneTag シーンのタグ
@param _playerPtr プレイヤーのポインタ
*/
LeftBlock::LeftBlock(const Vector3& _Pos, const Vector3& _Size, const float _AddPosX, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
	: GameObject(_SceneTag, _ObjectTag)
	, mElapseTime(0.0f)
	, mDifferencePos(0.0f)
	, mStart(0.0f)
	, mInversionPos(Vector3::sZERO)
	, mShakeFlag(false)
	, mReversFlag(false)
{
	// 反転する地点までの距離
	const float Distance = 60.0f;

	//GameObjectメンバ変数の初期化
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;

	mEndPos = Vector3(_Pos.x - _AddPosX, _Pos.y, _Pos.z);
	mInversionPos = Vector3(_Pos.x + Distance, _Pos.y, _Pos.z);

	//生成したLeftBlockの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	//矩形当たり判定
	const AABB Box = AABB(Vector3(-1.0f, -1.0f, -1.0f), Vector3(1.0f, 1.0f, 1.0f));

	mBoxcollider = new BoxCollider(this, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(Box);

	mOriginalPosFlag = false;

	mPlayer = _playerPtr;
}

/*
@fn		左移動床のアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void LeftBlock::UpdateGameObject(float _deltaTime)
{
	//プレイヤーの座標
	Vector3 playerPos = mPlayer->GetPosition();
	//距離
	float distance = 2040.0f;
	//予知動作を開始するためのz座標
	float ShakeZPos = mPosition.z - distance;

	//////////////////////////////////////
	//予知動作処理
	if (playerPos.z >= ShakeZPos)
	{
		mShakeFlag = true;
	}

	if (mShakeFlag)
	{
		if (mPosition.x >= mInversionPos.x)
		{
			mReversFlag = true;
		}
		else if (mPosition.x <= mInitPos.x)
		{
			mReversFlag = false;
		}

		//左移動床の左に移動する速度
		const float LeftSpeed = 20.0f;

		if (mReversFlag == true)
		{
			mVelocity.x = -LeftSpeed;
		}
		else if (mReversFlag == false)
		{
			mVelocity.x = LeftSpeed;
		}
		
	}
	/////////////////////////////////////////

	distance = 1800.0f;
	//動き始めるためのz座標
	const float MoveZPos = mPosition.z - distance;

	if (playerPos.z >= MoveZPos)
	{
		//全体の時間
		const float TotarlTime = 1.0f;

		mShakeFlag = false;
		mElapseTime += _deltaTime;
		mDifferencePos = mEndPos.x - mInitPos.x;
		mVelocity.x = -Quartic::EaseIn(mElapseTime, mStart, -mDifferencePos, TotarlTime) * 0.02f;
	}


	if (mInitPos.x > mPosition.x)
	{
		mOriginalPosFlag = true;
	}

	if (mPosition.x <= mEndPos.x)
	{
		mVelocity.x = 0.0f;
	}

	if (mPlayer->GetDeathFlag())
	{
		mElapseTime = 0.0f;
		mVelocity.x = 0.0f;
		mOriginalPosFlag = false;
	}

	if (mOriginalPosFlag)
	{
		if (mPlayer->GetRespawnFlag())
		{
			mElapseTime = 0.0f;
			mVelocity.x = 0.0f;
			mPosition.x = mInitPos.x;
			mShakeFlag = false;
			mOriginalPosFlag = false;
		}
	}
	
	// 常に座標に速度を足す
	mPosition += mVelocity;

	SetPosition(mPosition);
}