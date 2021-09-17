/*
@brief �C���N���[�h
*/
#include <iostream>

#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �c�ړ����̍��W
@param	_Size �c�ړ����̃T�C�Y
@param	_ObjectTag �c�ړ����̃^�O
@param	_SceneTag �V�[���̃^�O
@param _playerPtr �v���C���[�̃|�C���^
*/
VerticalMoveGround::VerticalMoveGround(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr) :
	GameObject(_SceneTag, _ObjectTag)
{
	//�I���n�_�܂ł̋���
	const float Distance = 200.0f;

	//GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;

	mEndPos = Vector3(_Pos.x, _Pos.y, _Pos.z + Distance);

	//��������VerticalMoveGround�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	// �����蔻��
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_GpmeshName);
	mBoxcollider = new BoxCollider(this, ColliderTag::eVerticalMoveGroundTag, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());

	mOriginalPosFlag = false;

	mPlayer = _playerPtr;
}

/*
@fn		�c�ړ����̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void VerticalMoveGround::UpdateGameObject(float _deltaTime)
{
	if (mPosition.z >= mEndPos.z)
	{
		mVelocity.z = 0.0f;
	}

	if (mOriginalPosFlag)
	{
		if (mPlayer->GetRespawnFlag())
		{
			mVelocity.z = 0.0f;
			mPosition = mInitPos;
			mOriginalPosFlag = false;
		}
	}

	// ��ɍ��W�ɑ��x�𑫂�
	mPosition += mVelocity;

	SetPosition(mPosition);
}

/*
@fn		�c�ړ������q�b�g�������̏���
@param	_HitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
*/
void VerticalMoveGround::OnCollision(const GameObject& _HitObject)
{
	//�c�ړ����̑O�Ɉړ����鑬�x
	const float ForwardSpeed = 10.0f;

	mOriginalPosFlag = true;
	mVelocity.z = ForwardSpeed;
}