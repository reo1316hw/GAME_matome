/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos ジャンプ床の座標
@param	_Size ジャンプ床のサイズ
@param	_ObjectTag ジャンプ床のタグ
@param	_SceneTag シーンのタグ
*/
Jump::Jump(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr) :
	GameObject(_SceneTag, _ObjectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;

	degree = 0.0f;
	mVelocity = Vector3::sZERO;

	//生成したJumpの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	//矩形当たり判定
	const AABB Box = AABB(Vector3(-1.0f, -1.0f, -1.0f), Vector3(1.0f, 1.0f, 1.0f));

	mBoxcollider = new BoxCollider(this, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(Box);

	mPlayer = _playerPtr;
}

/*
@fn		ジャンプ床のアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void Jump::UpdateGameObject(float _deltaTime)
{
	if (mPlayer->GetRespawnFlag())
	{
		mHitFlag = false;
		mVelocity = Vector3::sZERO;
		mPosition = mInitPos;
		degree = 0.0f;
	}

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
@param	_HitObject ヒットした対象のゲームオブジェクトのアドレス
*/
void Jump::OnCollision(const GameObject& _HitObject)
{
	mHitFlag = true;
}