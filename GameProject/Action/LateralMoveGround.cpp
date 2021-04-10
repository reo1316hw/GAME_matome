#include "LateralMoveGround.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"

Vector3 LateralMoveGround::mSendVel = Vector3::Zero;

LateralMoveGround::LateralMoveGround(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const float _distance)
	: GameObject(_sceneTag, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// �ړ���̍��W
	mEndPos = Vector3(_pos.x - _distance, _pos.y, _pos.z) ;
	// �����̍��W
	mInitPos = _pos;

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//��������LateralMoveGround�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		mMeshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box.gpmesh"));

		// �����蔻��
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh("Assets/box.gpmesh");
		mBoxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		mBoxcollider->SetObjectBox(mMesh->GetBox());

		break;
	case SceneBase::Scene::stage01:

		//��������LateralMoveGround�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		mMeshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box_08.gpmesh"));

		// �����蔻��
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh("Assets/box_08.gpmesh");
		mBoxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		mBoxcollider->SetObjectBox(mMesh->GetBox());

		break;

	case SceneBase::Scene::stage02:

		//��������LateralMoveGround�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		mMeshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box_13.gpmesh"));

		// �����蔻��
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh("Assets/box_13.gpmesh");
		mBoxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		mBoxcollider->SetObjectBox(mMesh->GetBox());

		break;
	}

	// ���]�t���O
	mReversFlag = false;
	mOriginalPosFlag = false;
}

void LateralMoveGround::UpdateGameObject(float _deltaTime)
{
	if (mInitPos.x != mPosition.x)
	{
		mOriginalPosFlag = true;
	}

	if (Player::GetDeathFlag())
	{
		mVelocity.x = 0.0f;
		mOriginalPosFlag = false;
	}

	if (mOriginalPosFlag)
	{
		if (Player::GetRespawnFlag())
		{
			mVelocity.x = 0.0f;
			mPosition.x = mInitPos.x;
			mOriginalPosFlag = false;
		}
	}

	if (mPosition.x <= mEndPos.x)
	{
		mReversFlag = true;
	}
	else if (mPosition.x >= mInitPos.x)
	{
		mReversFlag = false;
	}

	if (mReversFlag == true )
	{
		mVelocity.x = 10.0f;
		
	}
	else if(mReversFlag == false)
	{
		mVelocity.x = -10.0f;
	}

	mSendVel = mVelocity;
	mPosition += mVelocity;

	SetPosition(mPosition);
}