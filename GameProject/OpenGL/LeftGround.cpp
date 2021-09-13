/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_pos 1マス左移動床の座標
@param	_size 1マス左移動床のサイズ
@param	_objectTag 1マス左移動床のタグ
@param	_sceneTag シーンのタグ
@param _playerPtr プレイヤーのポインタ
*/
LeftGround::LeftGround(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag, Player* _playerPtr)
	: GameObject(_sceneTag, _objectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);
	mInitPos = _pos;

	mEndPos = Vector3(_pos.x - 200, _pos.y, _pos.z);

	//生成したLeftOneBlockの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));

	// 当たり判定
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_gpmeshName);
	mBoxcollider = new BoxCollider(this, ColliderTag::leftGroundTag, GetOnCollisionFunc());
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
	Vector3 playerPos = mPlayer->GetPosition();

	if (playerPos.z >= mPosition.z - 600.0f)
	{
		mVelocity.x = -LEFT_SPEED;
	}

	if (mInitPos.x > mPosition.x)
	{
		mOriginalPosFlag = true;
	}

	if (mPosition.x <= mEndPos.x)
	{
		mVelocity.x = 0;
	}

	if (mPlayer->GetDeathFlag())
	{
		mVelocity.x = 0;
		mOriginalPosFlag = false;
	}

	if (mOriginalPosFlag)
	{
		if (mPlayer->GetRespawnFlag())
		{
			mVelocity.x = 0;
			mPosition.x = mInitPos.x;
			mOriginalPosFlag = false;
		}
	}

	// 常に座標に速度を足す
	mPosition += mVelocity;

	SetPosition(mPosition);
}
