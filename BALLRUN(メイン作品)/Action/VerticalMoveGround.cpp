#include "VerticalMoveGround.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include <iostream>

VerticalMoveGround::VerticalMoveGround(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag) :
	GameObject(_sceneTag,objectTag)
{
	//GameObject�����o�ϐ��̏�����
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	tmpPos = Vector3(_pos.x, _pos.y, _pos.z + 200);

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		meshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_04.gpmesh"));

		// �����蔻��
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box_04.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;
	case SceneBase::Scene::stage01:

		//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		meshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_11.gpmesh"));

		// �����蔻��
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box_11.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;

	case SceneBase::Scene::stage02:

		//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		meshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_16.gpmesh"));

		// �����蔻��
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

	// ��ɍ��W�ɑ��x�𑫂�
	position += velocity;

	SetPosition(position);
}

// �����蔻��
void VerticalMoveGround::OnCollision(const GameObject& _hitObject)
{
	hitFlag = true;

	if (hitFlag)
	{
		originalPosFlag = true;
		velocity.z = FORWARD_SPEED;
	}
}