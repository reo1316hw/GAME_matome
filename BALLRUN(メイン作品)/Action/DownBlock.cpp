#include "DownBlock.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Player.h"

DownBlock::DownBlock(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	mEndPos = Vector3(_pos.x, _pos.y - 1600, _pos.z);

	//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box_13.gpmesh"));

	// 当たり判定
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh("Assets/box_13.gpmesh");
	mBoxcollider = new BoxCollider(this, ColliderTag::downBlockTag, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());
}

void DownBlock::UpdateGameObject(float _deltaTime)
{
	Vector3 playerPos = Player::GetPos();

	if (playerPos.z >= mPosition.z - 3000.0f)
	{
		mVelocity.y = -DOWN_SPEED;
	}

	if (mPosition == mEndPos)
	{
		mVelocity.y = 0;
	}

	if (Player::GetRespawnFlag())
	{
		mPosition.y = 1600;
	}

	// 常に座標に速度を足す
	mPosition += mVelocity;

	SetPosition(mPosition);
}