#include "LeftBlock.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Player.h"

LeftBlock::LeftBlock(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, objectTag)
	, elapseTime(0.0f)
	, differencePos(0.0f)
	, start(0.0f)
	, inversionPos(Vector3::Zero)
	, shakeFlag(false)
	, reversFlag(false)
{
	//GameObjectメンバ変数の初期化
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);
	
	initPos = Vector3(_pos.x, _pos.y, _pos.z);
	endPos = Vector3(_pos.x - 600, _pos.y, _pos.z);
	inversionPos = Vector3(_pos.x + 60, _pos.y, _pos.z);

	//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	meshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_15.gpmesh"));

	// 当たり判定
	mesh = new Mesh;
	mesh = RENDERER->GetMesh("Assets/box_15.gpmesh");
	boxcollider = new BoxCollider(this, ColliderTag::leftBlockTag, GetOnCollisionFunc());
	boxcollider->SetObjectBox(mesh->GetBox());

	originalPosFlag = false;
}

void LeftBlock::UpdateGameObject(float _deltaTime)
{
	Vector3 playerPos = Player::GetPos();

	//////////////////////////////////////
	//予知動作処理
	if (playerPos.z >= position.z - 2040.0f)
	{
		shakeFlag = true;
	}

	if (shakeFlag)
	{
		if (position.x >= inversionPos.x)
		{
			reversFlag = true;
		}
		else if (position.x <= initPos.x)
		{
			reversFlag = false;
		}

		if (reversFlag == true)
		{
			velocity.x = -LEFT_SPEED;
		}
		else if (reversFlag == false)
		{
			velocity.x = LEFT_SPEED;
		}
		
	}
	/////////////////////////////////////////

	if (playerPos.z >= position.z - 1800.0f)
	{
		shakeFlag = false;
		elapseTime += _deltaTime;
		differencePos = endPos.x - initPos.x;
		velocity.x = -Quartic::EaseIn(elapseTime, start, -differencePos, totalTime) * 0.02f;
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
		elapseTime = 0.0f;
		velocity.x = 0;
		originalPosFlag = false;
	}

	if (originalPosFlag)
	{
		if (Player::GetRespawnFlag())
		{
			elapseTime = 0.0f;
			velocity.x = 0;
			position.x = initPos.x;
			originalPosFlag = false;
		}
	}
	
	// 常に座標に速度を足す
	position += velocity;

	SetPosition(position);
}