#include "VerticalMoveGround.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include <iostream>

VerticalMoveGround::VerticalMoveGround(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag) :
	GameObject(_sceneTag,_objectTag)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	mEndPos = Vector3(_pos.x, _pos.y, _pos.z + 200);

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//��������VerticalMoveGround�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		mMeshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box_04.gpmesh"));

		// �����蔻��
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh("Assets/box_04.gpmesh");
		mBoxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		mBoxcollider->SetObjectBox(mMesh->GetBox());

		break;
	case SceneBase::Scene::stage01:

		//��������VerticalMoveGround�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		mMeshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box_11.gpmesh"));

		// �����蔻��
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh("Assets/box_11.gpmesh");
		mBoxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		mBoxcollider->SetObjectBox(mMesh->GetBox());

		break;

	case SceneBase::Scene::stage02:

		//��������VerticalMoveGround�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		mMeshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box_16.gpmesh"));

		// �����蔻��
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh("Assets/box_16.gpmesh");
		mBoxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		mBoxcollider->SetObjectBox(mMesh->GetBox());

		break;
	}

	mOriginalPosFlag = false;
}

void VerticalMoveGround::UpdateGameObject(float _deltaTime)
{
	if (mPosition == mEndPos)
	{
		mVelocity.z = 0;
	}

	if (mOriginalPosFlag)
	{
		if (Player::GetRespawnFlag())
		{
			mPosition.z = mPosition.z - 200;
			mOriginalPosFlag = false;
		}
	}

	// ��ɍ��W�ɑ��x�𑫂�
	mPosition += mVelocity;

	SetPosition(mPosition);
}

// �����蔻��
void VerticalMoveGround::OnCollision(const GameObject& _hitObject)
{
	mOriginalPosFlag = true;
	mVelocity.z = FORWARD_SPEED;
}