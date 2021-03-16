#include "LeftOneBlock.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Player.h"

LeftOneBlock::LeftOneBlock(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, objectTag)
{
	//GameObjectメンバ変数の初期化
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	initPos = Vector3(_pos.x, _pos.y, _pos.z);
	endPos = Vector3(_pos.x - 200, _pos.y, _pos.z);

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		meshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_07.gpmesh"));

		// 当たり判定
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box_07.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::rightOneBlockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;

	case SceneBase::Scene::stage02:

		//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		meshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_19.gpmesh"));

		// 当たり判定
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box_19.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::leftOneBlockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;
	}

	originalPosFlag = false;
}

void LeftOneBlock::UpdateGameObject(float _deltaTime)
{
	Vector3 playerPos = Player::GetPos();

	if (playerPos.z >= position.z - 600.0f)
	{
		velocity.x = -LEFT_SPEED;
	}

	if (initPos.x > position.x)
	{
		originalPosFlag = true;
	}

	if (position.x <= endPos.x)
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
