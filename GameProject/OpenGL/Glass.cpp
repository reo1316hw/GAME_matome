/*
@brief インクルード
*/
#include "pch.h"

/*
@fn	   コンストラクタ
@param _Pos ガラス床の座標
@param _Size ガラス床のサイズ
@param _ObjectTag ガラス床のタグ
@param _SceneTag シーンのタグ
@param _playerPtr プレイヤーのポインタ
*/
Glass::Glass(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag,const SceneBase::Scene _SceneTag, Player* _playerPtr) :
	GameObject(_SceneTag,_ObjectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;

	mDownCount = 0;

	//生成したGlassの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mInvisibleMeshComponent = new InvisibleMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mInvisibleMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	//矩形当たり判定
	const AABB Box = AABB(Vector3(-1.0f, -1.0f, -1.0f), Vector3(1.0f, 1.0f, 1.0f));

	mBoxcollider = new BoxCollider(this, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(Box);

	mPlayer = _playerPtr;
}

/*
@fn		ガラス床のアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void Glass::UpdateGameObject(float _deltaTime)
{
	// 落とすためのカウントの上限値
	const int LimitDownCount = 16;

	if (mPlayer->GetRespawnFlag())
	{
		mHitFlag = false;
		mDownCount = 0;
		mVelocity.y = 0.0f;
		mPosition = mInitPos;
	}

	if (mHitFlag)
	{
		mDownCount++;
	}

	// 落とすためのカウントが上限値まで達したらガラス床が落ちる
	if (mDownCount >= LimitDownCount)
	{
		// 落ちるスピード
		const float DownSpeed = 100.0f;

		mVelocity.y = -DownSpeed;
	}

	// 常に座標に速度を足す
	mPosition += mVelocity;

	SetPosition(mPosition);
}

/*
@fn		ガラス床がヒットした時の処理
@param	_HitObject ヒットした対象のゲームオブジェクトのアドレス
*/
void Glass::OnCollision(const GameObject& _HitObject)
{
	mHitFlag = true;
}
