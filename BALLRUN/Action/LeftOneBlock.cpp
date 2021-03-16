#include "LeftOneBlock.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Player.h"

LeftOneBlock::LeftOneBlock(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, objectTag)
{
	//GameObject�����o�ϐ��̏�����
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	initPos = Vector3(_pos.x, _pos.y, _pos.z);
	endPos = Vector3(_pos.x - 200, _pos.y, _pos.z);

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		meshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_07.gpmesh"));

		// �����蔻��
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box_07.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::rightOneBlockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;

	case SceneBase::Scene::stage02:

		//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		meshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_19.gpmesh"));

		// �����蔻��
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

	// ��ɍ��W�ɑ��x�𑫂�
	position += velocity;

	SetPosition(position);
}
