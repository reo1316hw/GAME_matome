/*
@brief	インクルード
*/
#include "LateralMoveGround.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"



Vector3 LateralMoveGround::mSendVel = Vector3::Zero;




/*
@fn		コンストラクタ
@param	_pos 横移動床の座標
@param	_size 横移動床のサイズ
@param	_objectTag 横移動床のタグ
@param	_sceneTag シーンのタグ
@param _distance 横移動床の移動する距離
*/
LateralMoveGround::LateralMoveGround(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const float _distance)
	: GameObject(_sceneTag, _objectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// 移動先の座標
	mEndPos = Vector3(_pos.x - _distance, _pos.y, _pos.z) ;
	// 初期の座標
	mInitPos = _pos;

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//生成したLateralMoveGroundの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		mMeshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box.gpmesh"));

		// 当たり判定
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh("Assets/box.gpmesh");
		mBoxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		mBoxcollider->SetObjectBox(mMesh->GetBox());

		break;
	case SceneBase::Scene::stage01:

		//生成したLateralMoveGroundの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		mMeshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box_08.gpmesh"));

		// 当たり判定
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh("Assets/box_08.gpmesh");
		mBoxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		mBoxcollider->SetObjectBox(mMesh->GetBox());

		break;

	case SceneBase::Scene::stage02:

		//生成したLateralMoveGroundの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		mMeshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box_13.gpmesh"));

		// 当たり判定
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh("Assets/box_13.gpmesh");
		mBoxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		mBoxcollider->SetObjectBox(mMesh->GetBox());

		break;
	}

	// 反転フラグ
	mReversFlag = false;
	mOriginalPosFlag = false;
}

/*
@fn		横移動床のアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void LateralMoveGround::UpdateGameObject(float _deltaTime)
{
	if (mInitPos.x != mPosition.x)
	{
		mOriginalPosFlag = true;
	}

	if (Player::GetDeathFlag())
	{
		mVelocity.x = 0.0f;
		mOriginalPosFlag = false;
	}

	if (mOriginalPosFlag)
	{
		if (Player::GetRespawnFlag())
		{
			mVelocity.x = 0.0f;
			mPosition.x = mInitPos.x;
			mOriginalPosFlag = false;
		}
	}

	if (mPosition.x <= mEndPos.x)
	{
		mReversFlag = true;
	}
	else if (mPosition.x >= mInitPos.x)
	{
		mReversFlag = false;
	}

	if (mReversFlag == true )
	{
		mVelocity.x = MOVE_SPEED;
		
	}
	else if(mReversFlag == false)
	{
		mVelocity.x = -MOVE_SPEED;
	}

	mSendVel = mVelocity;
	mPosition += mVelocity;

	SetPosition(mPosition);
}