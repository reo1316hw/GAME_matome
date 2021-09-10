/*
@brief	インクルード
*/
#include <iostream>

#include "pch.h"

/*
@fn		コンストラクタ
@param	_pos 縦移動床の座標
@param	_size 縦移動床のサイズ
@param	_objectTag 縦移動床のタグ
@param	_sceneTag シーンのタグ
@param _playerPtr プレイヤーのポインタ
*/
VerticalMoveGround::VerticalMoveGround(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag, Player* _playerPtr) :
	GameObject(_sceneTag,_objectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	mEndPos = Vector3(_pos.x, _pos.y, _pos.z + 200);

	//生成したVerticalMoveGroundの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));

	// 当たり判定
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_gpmeshName);
	mBoxcollider = new BoxCollider(this, ColliderTag::verticalMoveGroundTag, GetOnCollisionFunc());
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
		mVelocity.z = 0;
	}

	if (mOriginalPosFlag)
	{
		if (mPlayer->GetRespawnFlag())
		{
			mPosition.z = mPosition.z - 200;
			mOriginalPosFlag = false;
		}
	}

	// 常に座標に速度を足す
	mPosition += mVelocity;

	SetPosition(mPosition);
}

/*
@fn		縦移動床がヒットした時の処理
@param	_hitObject ヒットした対象のゲームオブジェクトのアドレス
*/
void VerticalMoveGround::OnCollision(const GameObject& _hitObject)
{
	mOriginalPosFlag = true;
	mVelocity.z = FORWARD_SPEED;
}