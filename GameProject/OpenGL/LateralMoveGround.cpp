/*
@brief インクルード
*/
#include "pch.h"

Vector3 LateralMoveGround::mSendVel = Vector3::sZERO;

/*
@fn		コンストラクタ
@param	_Pos 横移動床の座標
@param	_Size 横移動床のサイズ
@param	_ObjectTag 横移動床のタグ
@param	_SceneTag シーンのタグ
@param _distance 横移動床の移動する距離
@param _playerPtr プレイヤーのポインタ
*/
LateralMoveGround::LateralMoveGround(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, const float _Distance, Player* _playerPtr)
	: GameObject(_SceneTag, _ObjectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	// 初期の座標
	mInitPos = _Pos;

	// 移動先の座標
	mEndPos = Vector3(_Pos.x - _Distance, _Pos.y, _Pos.z) ;

	//生成したLateralMoveGroundの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	// 当たり判定
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_GpmeshName);
	mBoxcollider = new BoxCollider(this, ColliderTag::eLateralMoveGroundTag, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());

	// 反転フラグ
	mReversFlag = false;
	mOriginalPosFlag = false;

	mPlayer = _playerPtr;
}

/*
@fn		横移動床のアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void LateralMoveGround::UpdateGameObject(float _deltaTime)
{
	if (mInitPos.x != mPosition.x)
	{
		mOriginalPosFlag = true;
	}

	if (mPlayer->GetDeathFlag())
	{
		mVelocity.x = 0.0f;
		mOriginalPosFlag = false;
	}

	if (mOriginalPosFlag)
	{
		if (mPlayer->GetRespawnFlag())
		{
			mVelocity.x = 0.0f;
			mPosition = mInitPos;
			mOriginalPosFlag = false;
		}
	}

	if (mPosition.x <= mEndPos.x)
	{
		mReversFlag = true;
	}
	else if (mPosition.x >= mInitPos.x)
	{
		mReversFlag = false;
	}

	//横移動するときの速度
	const float MoveSpeed = 10.0f;

	if (mReversFlag == true )
	{
		mVelocity.x = MoveSpeed;
		
	}
	else if(mReversFlag == false)
	{
		mVelocity.x = -MoveSpeed;
	}

	mSendVel = mVelocity;
	mPosition += mVelocity;

	SetPosition(mPosition);
}