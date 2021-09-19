/*
@brief インクルード
*/
#include "pch.h"

/*
@fn	   コンストラクタ
@param _Pos 落下ブロックの座標
@param _Size 落下ブロックのサイズ
@param _ObjectTag 落下ブロックのタグ
@param _SceneTag シーンのタグ
@param _playerPtr プレイヤーのポインタ
*/
DownBlock::DownBlock(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
	: GameObject(_SceneTag, _ObjectTag)
{
	// 終了地点までの距離
	const float Distance = 1600.0f;

	//GameObjectメンバ変数の初期化
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;

	mEndPos = Vector3(_Pos.x, _Pos.y - Distance, _Pos.z);

	//生成したDownBlockの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	// 当たり判定
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_GpmeshName);
	mBoxcollider = new BoxCollider(this, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());

	mPlayer = _playerPtr;
}

/*
@fn		落下ブロックのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void DownBlock::UpdateGameObject(float _deltaTime)
{
	//プレイヤーの座標
	Vector3 playerPos = mPlayer->GetPosition();
	//距離
	const float Distance = 3000.0f;

	if (playerPos.z >= mPosition.z - Distance)
	{
		//落下ブロックの落ちる速度
		const float DownSpeed = 25.0f;

		mVelocity.y = -DownSpeed;
	}

	if (mPosition.y <= mEndPos.y)
	{
		mVelocity.y = 0.0f;
	}

	if (mPlayer->GetRespawnFlag())
	{
		mPosition = mInitPos;
		mVelocity.y = 0.0f;
	}

	// 常に座標に速度を足す
	mPosition += mVelocity;

	SetPosition(mPosition);
}