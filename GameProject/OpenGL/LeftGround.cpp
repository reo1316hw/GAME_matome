/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos 1マス左移動床の座標
@param	_Size 1マス左移動床のサイズ
@param	_ObjectTag 1マス左移動床のタグ
@param	_SceneTag シーンのタグ
@param _playerPtr プレイヤーのポインタ
*/
LeftGround::LeftGround(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
	: GameObject(_SceneTag, _ObjectTag)
{
	// 終了地点までの距離
	const float Distance = 200.0f;

	//GameObjectメンバ変数の初期化
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;

	mEndPos = Vector3(_Pos.x - Distance, _Pos.y, _Pos.z);

	//生成したLeftOneBlockの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	// 当たり判定
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_GpmeshName);
	mBoxcollider = new BoxCollider(this, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());

	mOriginalPosFlag = false;

	mPlayer = _playerPtr;
}

/*
@fn		1マス左移動床のアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void LeftGround::UpdateGameObject(float _deltaTime)
{
	//プレイヤーの座標
	Vector3 playerPos = mPlayer->GetPosition();
	//距離
	const float Distance = 600.0f;

	if (playerPos.z >= mPosition.z - Distance)
	{
		//1マス左移動床の左に移動する速度
		const float LeftSpeed = 10.0f;

		mVelocity.x = -LeftSpeed;
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

	// 常に座標に速度を足す
	mPosition += mVelocity;

	SetPosition(mPosition);
}
