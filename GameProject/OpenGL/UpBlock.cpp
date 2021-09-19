/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos ��ړ��u���b�N�̍��W
@param	_Size ��ړ��u���b�N�̃T�C�Y
@param	_ObjectTag ��ړ��u���b�N�̃^�O
@param	_SceneTag �V�[���̃^�O
@param _playerPtr �v���C���[�̃|�C���^
*/
UpBlock::UpBlock(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
	: GameObject(_SceneTag, _ObjectTag)
{
	// �I���n�_�܂ł̋���
	const float Distance = 200.0f;

	//GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;

	mEndPos = Vector3(_Pos.x, _Pos.y + Distance, _Pos.z);

	//��������UpBlock�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	// �����蔻��
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_GpmeshName);
	mBoxcollider = new BoxCollider(this, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());

	mOriginalPosFlag = false;

	mPlayer = _playerPtr;
}

/*
@fn		��ړ��u���b�N�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void UpBlock::UpdateGameObject(float _deltaTime)
{
	//�v���C���[�̍��W
	Vector3 playerPos = mPlayer->GetPosition();
	//����
	const float Distance = 1000.0f;

	if (playerPos.z >= mPosition.z - Distance)
	{
		//��ړ��u���b�N�̏�Ɉړ����鑬�x
		const float UpSpeed = 10.0f;

		mVelocity.y = UpSpeed;
	}

	if (mInitPos.y < mPosition.y)
	{
		mOriginalPosFlag = true;
	}

	if (mPosition.y >= mEndPos.y)
	{
		mVelocity.y = 0.0f;
	}

	if (mPlayer->GetDeathFlag())
	{
		mVelocity.y = 0.0f;
		mOriginalPosFlag = false;
	}

	if (mOriginalPosFlag)
	{
		if (mPlayer->GetRespawnFlag())
		{
			mVelocity.y = 0.0f;
			mPosition = mInitPos;
			mOriginalPosFlag = false;
		}
	}

	// ��ɍ��W�ɑ��x�𑫂�
	mPosition += mVelocity;

	SetPosition(mPosition);
}
