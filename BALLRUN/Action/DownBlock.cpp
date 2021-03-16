#include "DownBlock.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Player.h"

DownBlock::DownBlock(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, objectTag)
{
	//GameObject�����o�ϐ��̏�����
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	endPos = Vector3(_pos.x, _pos.y - 1600, _pos.z);

	//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	meshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_13.gpmesh"));

	// �����蔻��
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

	// ��ɍ��W�ɑ��x�𑫂�
	position += velocity;

	SetPosition(position);
}