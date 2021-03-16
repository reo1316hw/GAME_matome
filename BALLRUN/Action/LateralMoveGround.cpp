#include "LateralMoveGround.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"

Vector3 LateralMoveGround::sendVel = Vector3::Zero;

LateralMoveGround::LateralMoveGround(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag, const float _distance)
	: GameObject(_sceneTag, objectTag)
{
	//GameObject�����o�ϐ��̏�����
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	velocity = Vector3::Zero;

	// �ړ���̍��W
	endPos = Vector3(_pos.x - _distance, _pos.y, _pos.z) ;
	// �����̍��W
	initPos = _pos;

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		meshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box.gpmesh"));

		// �����蔻��
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;
	case SceneBase::Scene::stage01:

		//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		meshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_08.gpmesh"));

		// �����蔻��
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box_08.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;

	case SceneBase::Scene::stage02:

		//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		meshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_13.gpmesh"));

		// �����蔻��
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box_13.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;
	}

	// ���]�t���O
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