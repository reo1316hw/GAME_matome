/*
@brief インクルード
*/
#include "pch.h"

/*
@fn	   コンストラクタ
@param _pos ガラス床の座標
@param _size ガラス床のサイズ
@param _objectTag ガラス床のタグ
@param _sceneTag シーンのタグ
@param _playerPtr プレイヤーのポインタ
*/
Glass::Glass(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag,const SceneBase::Scene _sceneTag, Player* _playerPtr) :
	GameObject(_sceneTag,_objectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);
	mInitPos = _pos;

	mDownCount = 0;

	//生成したGlassの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mInvisibleMeshComponent = new InvisibleMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mInvisibleMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));

	// 当たり判定
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_gpmeshName);
	mBoxcollider = new BoxCollider(this, ColliderTag::glassTag, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());

	mPlayer = _playerPtr;
}

/*
@fn		ガラス床のアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void Glass::UpdateGameObject(float _deltaTime)
{
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

	if (mDownCount >= 15)
	{
		mVelocity.y = -DOWN_SPEED;
	}

	// 常に座標に速度を足す
	mPosition += mVelocity;

	SetPosition(mPosition);
}

/*
@fn		ガラス床がヒットした時の処理
@param	_hitObject ヒットした対象のゲームオブジェクトのアドレス
*/
void Glass::OnCollision(const GameObject& _hitObject)
{
	mHitFlag = true;
}
