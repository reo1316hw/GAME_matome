#include "Glass.h"
//#include "InvisibleMeshComponent.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"

Glass::Glass(const Vector3& _pos, const Vector3& _size, const Tag& objectTag,const SceneBase::Scene _sceneTag) :
	GameObject(_sceneTag,objectTag)
{
	//GameObject�����o�ϐ��̏�����
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	count = 0;

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		meshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_02.gpmesh"));

		// �����蔻��
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box_02.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;
	case SceneBase::Scene::stage01:

		//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		meshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_09.gpmesh"));

		// �����蔻��
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box_09.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;
	case SceneBase::Scene::stage02:

		//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		meshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_14.gpmesh"));

		// �����蔻��
		mesh = new Mesh;
		mesh = RENDERER->GetMesh("Assets/box_14.gpmesh");
		boxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		boxcollider->SetObjectBox(mesh->GetBox());

		break;
	}

	hitFlag = false;
}

void Glass::UpdateGameObject(float _deltaTime)
{
	if (Player::GetRespawnFlag())
	{
		hitFlag = false;
		count = 0;
		velocity.y = 0;
		position.y = 0;
	}

	if (hitFlag)
	{
		count++;
	}

	if (count >= 15)
	{
		velocity.y = -DOWN_SPEED;
	}

	// ��ɍ��W�ɑ��x�𑫂�ugjk
	position += velocity;

	SetPosition(position);
}

// �����蔻��
void Glass::OnCollision(const GameObject& _hitObject)
{
	hitFlag = true;
}
