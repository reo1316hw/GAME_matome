#include "AerialBlock.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"

AerialBlock::AerialBlock(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, objectTag)
{
	//GameObject�����o�ϐ��̏�����
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//��������TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	meshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_15.gpmesh"));

	//�����蔻��
	mesh = new Mesh;
	mesh = RENDERER->GetMesh("Assets/box_15.gpmesh");
	boxcollider = new BoxCollider(this, ColliderTag::aerialBlockTag, GetOnCollisionFunc());
	boxcollider->SetObjectBox(mesh->GetBox());
}