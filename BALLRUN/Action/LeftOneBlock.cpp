#include "LeftOneBlock.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Player.h"

LeftOneBlock::LeftOneBlock(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	mInitPos = Vector3(_pos.x, _pos.y, _pos.z);
	mEndPos = Vector3(_pos.x - 200, _pos.y, _pos.z);

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//生成したLeftOneBlockの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		mMeshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box_07.gpmesh"));

		// 当たり判定
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh("Assets/box_07.gpmesh");
		mBoxcollider = new BoxCollider(this, ColliderTag::rightOneBlockTag, GetOnCollisionFunc());
		mBoxcollider->SetObjectBox(mMesh->GetBox());

		break;

	case SceneBase::Scene::stage02:

		//生成したLeftOneBlockの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		mMeshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box_19.gpmesh"));

		// 当たり判定
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh("Assets/box_19.gpmesh");
		mBoxcollider = new BoxCollider(this, ColliderTag::leftOneBlockTag, GetOnCollisionFunc());
		mBoxcollider->SetObjectBox(mMesh->GetBox());

		break;
	}

	mOriginalPosFlag = false;
}

void LeftOneBlock::UpdateGameObject(float _deltaTime)
{
	Vector3 playerPos = Player::GetPos();

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

	if (Player::GetDeathFlag())
	{
		mVelocity.x = 0;
		mOriginalPosFlag = false;
	}

	if (mOriginalPosFlag)
	{
		if (Player::GetRespawnFlag())
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
