#include "LeftOneBlock_02.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Player.h"

LeftOneBlock_02::LeftOneBlock_02(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, objectTag)
{
	//GameObjectメンバ変数の初期化
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	initPos = Vector3(_pos.x, _pos.y, _pos.z);
	tmpPos = Vector3(_pos.x - 200, _pos.y, _pos.z);

	//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	meshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_15.gpmesh"));

	// 当たり判定
	mesh = new Mesh;
	mesh = RENDERER->GetMesh("Assets/box_15.gpmesh");
	boxcollider = new BoxCollider(this, ColliderTag::leftOneBlock_02Tag, GetOnCollisionFunc());
	boxcollider->SetObjectBox(mesh->GetBox());

	originalPosFlag = false;
}

void LeftOneBlock_02::UpdateGameObject(float _deltaTime)
{
	Vector3 playerPos = Player::GetPos();

	if (playerPos.z >= position.z - 1000.0f)
	{
		velocity.x = -LEFT_SPEED;
	}

	if (initPos.x > position.x)
	{
		originalPosFlag = true;
	}

	if (position.x <= tmpPos.x)
	{
		velocity.x = 0;
	}


	if (Player::GetDeathFlag())
	{
		velocity.x = 0;
		originalPosFlag = false;
	}

	if (originalPosFlag)
	{
		if (Player::GetRespawnFlag())
		{
			velocity.x = 0;
			position.x = initPos.x;
			originalPosFlag = false;
		}
	}

	aabb = boxcollider->GetWorldBox();

	// 常に座標に速度を足す
	position += velocity;

	SetPosition(position);
}