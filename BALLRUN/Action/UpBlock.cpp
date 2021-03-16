#include "UpBlock.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Player.h"

UpBlock::UpBlock(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, objectTag)
{
	//GameObject�����o�ϐ��̏�����
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	initPos = Vector3(_pos.x, _pos.y, _pos.z);
	tmpPos = Vector3(_pos.x, _pos.y + 200, _pos.z);

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		meshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_03.gpmesh"));

		// �����蔻��
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box_03.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::upBlockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;

	case SceneBase::Scene::stage02:

		//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		meshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_15.gpmesh"));

		// �����蔻��
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box_15.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::upBlockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;
	}

	originalPosFlag = false;
}

void UpBlock::UpdateGameObject(float _deltaTime)
{
	Vector3 playerPos = Player::GetPos();

	if (playerPos.z >= position.z - 1000.0f)
	{
		velocity.y = UP_SPEED;
	}

	if (initPos.y < position.y)
	{
		originalPosFlag = true;
	}

	if (position == tmpPos)
	{
		velocity.y = 0;
	}

	if (Player::GetDeathFlag())
	{
		velocity.y = 0;
		originalPosFlag = false;
	}

	if (originalPosFlag)
	{
		if (Player::GetRespawnFlag())
		{
			velocity.y = 0;
			position.y = initPos.y;
			originalPosFlag = false;
		}
	}

	aabb = boxcollider->GetWorldBox();

	// ��ɍ��W�ɑ��x�𑫂�
	position += velocity;

	SetPosition(position);
}
