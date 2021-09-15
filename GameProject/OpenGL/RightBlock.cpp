/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_pos 右移動ブロックの座標
@param	_size 右移動ブロックのサイズ
@param	_objectTag 右移動ブロックのタグ
@param	_sceneTag シーンのタグ
@param _playerPtr プレイヤーのポインタ
*/
RightBlock::RightBlock(const Vector3& _pos, const Vector3& _size, const float _addEndPosX, const std::string _gpmeshName, const Tag& _objectTag, const ColliderTag& _colliderTag, const SceneBase::Scene _sceneTag, Player* _playerPtr)
	: GameObject(_sceneTag, _objectTag)
	, mElapseTime(0.0f)
	, mDifferencePos(0.0f)
	, mStart(0.0f)
	, mShakeFlag(false)
	, mInversionPos(Vector3::Zero)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);
	mInitPos = _pos;

	mEndPos = Vector3(_pos.x + _addEndPosX, _pos.y, _pos.z);
	mInversionPos = Vector3(_pos.x + 60.0f, _pos.y, _pos.z);

	//生成したRightBlockの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmMesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));

	// 当たり判定
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_gpmeshName);
	mBoxcollider = new BoxCollider(this, _colliderTag, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());

	mOriginalPosFlag = false;

	mPlayer = _playerPtr;
}

/*
@fn		右移動ブロックのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void RightBlock::UpdateGameObject(float _deltaTime)
{
	Vector3 playerPos = mPlayer->GetPosition();
	//////////////////////////////////////
	//予知動作処理

	if (playerPos.z >= mPosition.z - 2040.0f)
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

		if (mReversFlag == true)
		{
			mVelocity.x = -RIGHT_SPEED;
		}
		else if (mReversFlag == false)
		{
			mVelocity.x = RIGHT_SPEED;
		}
	}
	/////////////////////////////////////////

	if (playerPos.z >= mPosition.z - 1800.0f)
	{
		mShakeFlag = false;
		mElapseTime += _deltaTime;
		mDifferencePos = mEndPos.x - mInitPos.x;
		mVelocity.x = Quartic::EaseIn(mElapseTime, mStart , mDifferencePos, TOTAL_TIME) * 0.02f;
	}

	if (mInitPos.x < mPosition.x)
	{
		mOriginalPosFlag = true;
	}

	if (mPosition.x >= mEndPos.x)
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
			mPosition = mInitPos;
			mShakeFlag = false;
			mOriginalPosFlag = false;
		}
	}

	// 常に座標に速度を足す
	mPosition += mVelocity;

	SetPosition(mPosition);
}