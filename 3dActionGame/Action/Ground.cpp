#include "Ground.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"

Ground::Ground(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, objectTag)
{
	//GameObject�����o�ϐ��̏�����
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		meshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/box.gpmesh"));

		break;
	}
}

Ground::~Ground()
{
}

void Ground::UpdateGameObject(float _deltaTime)
{
	
}

void Ground::OnCollision(const GameObject& _hitObject)
{

}
