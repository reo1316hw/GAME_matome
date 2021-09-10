/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn	   コンストラクタ
@param _pos 落下ブロックの座標
@param _size 落下ブロックのサイズ
@param _objectTag 落下ブロックのタグ
@param _sceneTag シーンのタグ
@param _playerPtr プレイヤーのポインタ
*/
DownBlock::DownBlock(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag, Player* _playerPtr)
	: GameObject(_sceneTag, _objectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	mEndPos = Vector3(_pos.x, _pos.y - 1600, _pos.z);

	//生成したDownBlockの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));

	// 当たり判定
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_gpmeshName);
	mBoxcollider = new BoxCollider(this, ColliderTag::downBlockTag, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());

	mPlayer = _playerPtr;
}

/*
@fn		落下ブロックのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void DownBlock::UpdateGameObject(float _deltaTime)
{
	Vector3 playerPos = mPlayer->GetPosition();

	if (playerPos.z >= mPosition.z - 3000.0f)
	{
		mVelocity.y = -DOWN_SPEED;
	}

	if (mPosition.y <= mEndPos.y)
	{
		mVelocity.y = 0;
	}

	if (mPlayer->GetRespawnFlag())
	{
		mPosition.y = 1600;
	}

	// 常に座標に速度を足す
	mPosition += mVelocity;

	SetPosition(mPosition);
}