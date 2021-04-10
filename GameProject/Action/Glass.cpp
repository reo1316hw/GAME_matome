#include "Glass.h"
#include "InvisibleMeshComponent.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"

Glass::Glass(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag,const SceneBase::Scene _sceneTag) :
	GameObject(_sceneTag,_objectTag)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	mDownCount = 0;

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//��������Glass�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		mInvisibleMeshComponent = new InvisibleMeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		mInvisibleMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box_02.gpmesh"));

		// �����蔻��
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh("Assets/box_02.gpmesh");
		mBoxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		mBoxcollider->SetObjectBox(mMesh->GetBox());

		break;
	case SceneBase::Scene::stage01:

		//��������Glass�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		mInvisibleMeshComponent = new InvisibleMeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		mInvisibleMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box_09.gpmesh"));

		// �����蔻��
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh("Assets/box_09.gpmesh");
		mBoxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		mBoxcollider->SetObjectBox(mMesh->GetBox());

		break;
	case SceneBase::Scene::stage02:

		//��������Glass�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		mInvisibleMeshComponent = new InvisibleMeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		mInvisibleMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box_14.gpmesh"));

		// �����蔻��
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh("Assets/box_14.gpmesh");
		mBoxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		mBoxcollider->SetObjectBox(mMesh->GetBox());

		break;
	}
}

void Glass::UpdateGameObject(float _deltaTime)
{
	if (Player::GetRespawnFlag())
	{
		mHitFlag = false;
		mDownCount = 0;
		mVelocity.y = 0;
		mPosition.y = 0;
	}

	if (mHitFlag)
	{
		mDownCount++;
	}

	if (mDownCount >= 15)
	{
		mVelocity.y = -DOWN_SPEED;
	}

	// ��ɍ��W�ɑ��x�𑫂�
	mPosition += mVelocity;

	SetPosition(mPosition);
}

// �����蔻��
void Glass::OnCollision(const GameObject& _hitObject)
{
	mHitFlag = true;
}