#include "DownBlock.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Player.h"

DownBlock::DownBlock(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, objectTag)
{
	//GameObjectメンバ変数の初期化
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	endPos = Vector3(_pos.x, _pos.y - 1600, _pos.z);

	//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	meshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_13.gpmesh"));

	// 当たり判定
	mesh = new Mesh;
	mesh = RENDERER->GetMesh("Assets/box_13.gpmesh");
	boxcollider = new BoxCollider(this, ColliderTag::downBlockTag, GetOnCollisionFunc());
	boxcollider->SetObjectBox(mesh->GetBox());
}

void DownBlock::UpdateGameObject(float _deltaTime)
{
	Vector3 playerPos = Player::GetPos();

	if (playerPos.z >= position.z - 3000.0f)
	{
		velocity.y = -DOWN_SPEED;
	}

	if (position == endPos)
	{
		velocity.y = 0;
	}

	if (Player::GetRespawnFlag())
	{
		position.y = 1600;
	}

	aabb = boxcollider->GetWorldBox();

	// 常に座標に速度を足す
	position += velocity;

	SetPosition(position);
}