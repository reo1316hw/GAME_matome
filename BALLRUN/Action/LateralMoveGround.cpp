#include "LateralMoveGround.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"

Vector3 LateralMoveGround::sendVel = Vector3::Zero;

LateralMoveGround::LateralMoveGround(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag, const float _distance)
	: GameObject(_sceneTag, objectTag)
{
	//GameObjectメンバ変数の初期化
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	velocity = Vector3::Zero;

	// 移動先の座標
	endPos = Vector3(_pos.x - _distance, _pos.y, _pos.z) ;
	// 初期の座標
	initPos = _pos;

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		meshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box.gpmesh"));

		// 当たり判定
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;
	case SceneBase::Scene::stage01:

		//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		meshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_08.gpmesh"));

		// 当たり判定
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box_08.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;

	case SceneBase::Scene::stage02:

		//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		meshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_13.gpmesh"));

		// 当たり判定
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box_13.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;
	}

	// 反転フラグ
	reversFlag = false;
	originalPosFlag = false;
}

void LateralMoveGround::UpdateGameObject(float _deltaTime)
{
	if (initPos.x != position.x)
	{
		originalPosFlag = true;
	}

	if (Player::GetDeathFlag())
	{
		velocity.x = 0.0f;
		originalPosFlag = false;
	}

	if (originalPosFlag)
	{
		if (Player::GetRespawnFlag())
		{
			velocity.x = 0.0f;
			position.x = initPos.x;
			originalPosFlag = false;
		}
	}

	if (position.x <= endPos.x)
	{
		reversFlag = true;
	}
	else if (position.x >= initPos.x)
	{
		reversFlag = false;
	}

	if (reversFlag == true )
	{
		velocity.x = 10.0f;
		
	}
	else if(reversFlag == false)
	{
		velocity.x = -10.0f;
	}

	sendVel = velocity;
	position += velocity;

	SetPosition(position);
}