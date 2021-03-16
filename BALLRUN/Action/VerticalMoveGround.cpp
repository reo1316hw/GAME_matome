#include "VerticalMoveGround.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include <iostream>

VerticalMoveGround::VerticalMoveGround(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag) :
	GameObject(_sceneTag,objectTag)
{
	//GameObjectメンバ変数の初期化
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	tmpPos = Vector3(_pos.x, _pos.y, _pos.z + 200);

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		meshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_04.gpmesh"));

		// 当たり判定
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box_04.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;
	case SceneBase::Scene::stage01:

		//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		meshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_11.gpmesh"));

		// 当たり判定
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box_11.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;

	case SceneBase::Scene::stage02:

		//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		meshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_16.gpmesh"));

		// 当たり判定
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box_16.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;
	}

	originalPosFlag = false;

	hitFlag = false;
}

void VerticalMoveGround::UpdateGameObject(float _deltaTime)
{
	if (position == tmpPos)
	{
		velocity.z = 0;
	}

	if (originalPosFlag)
	{
		if (Player::GetRespawnFlag())
		{
			position.z = position.z - 200;
			originalPosFlag = false;
		}
	}

	aabb = boxcollider->GetWorldBox();

	// 常に座標に速度を足す
	position += velocity;

	SetPosition(position);
}

// 当たり判定
void VerticalMoveGround::OnCollision(const GameObject& _hitObject)
{
	hitFlag = true;

	if (hitFlag)
	{
		originalPosFlag = true;
		velocity.z = FORWARD_SPEED;
	}
}