/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_pos ジャンプ床の座標
@param	_size ジャンプ床のサイズ
@param	_objectTag ジャンプ床のタグ
@param	_sceneTag シーンのタグ
*/
Jump::Jump(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag) :
	GameObject(_sceneTag, _objectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	degree = 0.0f;
	mVelocity = Vector3::Zero;

	//生成したJumpの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));

	// 当たり判定
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_gpmeshName);
	mBoxcollider = new BoxCollider(this, ColliderTag::jumpTag, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());
}

void Jump::UpdateGameObject(float _deltaTime)
{
	if (mHitFlag)
	{
		// sinカーブ
		mVelocity.y = sinf(degree) * 8.0f;
		mVelocity.z = sinf(degree) * 8.0f;
		degree += 0.2f;

		if (degree >= 6.5f)
		{
			degree = 0.0f;
			mVelocity.y = 0.0f;
			mVelocity.z = 0.0f;
			mHitFlag = false;
		}
	}

	// 常に座標に速度を足す
	mPosition += mVelocity;

	SetPosition(mPosition);
}

/*
@fn		ジャンプ床がヒットした時の処理
@param	_hitObject ヒットした対象のゲームオブジェクトのアドレス
*/
void Jump::OnCollision(const GameObject& _hitObject)
{
	mHitFlag = true;
}