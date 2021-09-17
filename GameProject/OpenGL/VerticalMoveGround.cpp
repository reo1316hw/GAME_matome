/*
@brief インクルード
*/
#include <iostream>

#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos 縦移動床の座標
@param	_Size 縦移動床のサイズ
@param	_ObjectTag 縦移動床のタグ
@param	_SceneTag シーンのタグ
@param _playerPtr プレイヤーのポインタ
*/
VerticalMoveGround::VerticalMoveGround(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr) :
	GameObject(_SceneTag, _ObjectTag)
{
	//終了地点までの距離
	const float Distance = 200.0f;

	//GameObjectメンバ変数の初期化
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;

	mEndPos = Vector3(_Pos.x, _Pos.y, _Pos.z + Distance);

	//生成したVerticalMoveGroundの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	// 当たり判定
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_GpmeshName);
	mBoxcollider = new BoxCollider(this, ColliderTag::eVerticalMoveGroundTag, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());

	mOriginalPosFlag = false;

	mPlayer = _playerPtr;
}

/*
@fn		縦移動床のアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void VerticalMoveGround::UpdateGameObject(float _deltaTime)
{
	if (mPosition.z >= mEndPos.z)
	{
		mVelocity.z = 0.0f;
	}

	if (mOriginalPosFlag)
	{
		if (mPlayer->GetRespawnFlag())
		{
			mVelocity.z = 0.0f;
			mPosition = mInitPos;
			mOriginalPosFlag = false;
		}
	}

	// 常に座標に速度を足す
	mPosition += mVelocity;

	SetPosition(mPosition);
}

/*
@fn		縦移動床がヒットした時の処理
@param	_HitObject ヒットした対象のゲームオブジェクトのアドレス
*/
void VerticalMoveGround::OnCollision(const GameObject& _HitObject)
{
	//縦移動床の前に移動する速度
	const float ForwardSpeed = 10.0f;

	mOriginalPosFlag = true;
	mVelocity.z = ForwardSpeed;
}