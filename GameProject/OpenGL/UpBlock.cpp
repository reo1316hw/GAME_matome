/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos 上移動ブロックの座標
@param	_Size 上移動ブロックのサイズ
@param	_ObjectTag 上移動ブロックのタグ
@param	_SceneTag シーンのタグ
@param _playerPtr プレイヤーのポインタ
*/
UpBlock::UpBlock(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
	: GameObject(_SceneTag, _ObjectTag)
{
	// 終了地点までの距離
	const float Distance = 200.0f;

	//GameObjectメンバ変数の初期化
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;

	mEndPos = Vector3(_Pos.x, _Pos.y + Distance, _Pos.z);

	//生成したUpBlockの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
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
@fn		上移動ブロックのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void UpBlock::UpdateGameObject(float _deltaTime)
{
	//プレイヤーの座標
	Vector3 playerPos = mPlayer->GetPosition();
	//距離
	const float Distance = 1000.0f;

	if (playerPos.z >= mPosition.z - Distance)
	{
		//上移動ブロックの上に移動する速度
		const float UpSpeed = 10.0f;

		mVelocity.y = UpSpeed;
	}

	if (mInitPos.y < mPosition.y)
	{
		mOriginalPosFlag = true;
	}

	if (mPosition.y >= mEndPos.y)
	{
		mVelocity.y = 0.0f;
	}

	if (mPlayer->GetDeathFlag())
	{
		mVelocity.y = 0.0f;
		mOriginalPosFlag = false;
	}

	if (mOriginalPosFlag)
	{
		if (mPlayer->GetRespawnFlag())
		{
			mVelocity.y = 0.0f;
			mPosition = mInitPos;
			mOriginalPosFlag = false;
		}
	}

	// 常に座標に速度を足す
	mPosition += mVelocity;

	SetPosition(mPosition);
}
