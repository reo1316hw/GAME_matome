/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn	   �R���X�g���N�^
@param _Pos �����u���b�N�̍��W
@param _Size �����u���b�N�̃T�C�Y
@param _ObjectTag �����u���b�N�̃^�O
@param _SceneTag �V�[���̃^�O
@param _playerPtr �v���C���[�̃|�C���^
*/
DownBlock::DownBlock(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
	: GameObject(_SceneTag, _ObjectTag)
{
	// �I���n�_�܂ł̋���
	const float Distance = 1600.0f;

	//GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;

	mEndPos = Vector3(_Pos.x, _Pos.y - Distance, _Pos.z);

	//��������DownBlock�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	// �����蔻��
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_GpmeshName);
	mBoxcollider = new BoxCollider(this, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());

	mPlayer = _playerPtr;
}

/*
@fn		�����u���b�N�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void DownBlock::UpdateGameObject(float _deltaTime)
{
	//�v���C���[�̍��W
	Vector3 playerPos = mPlayer->GetPosition();
	//����
	const float Distance = 3000.0f;

	if (playerPos.z >= mPosition.z - Distance)
	{
		//�����u���b�N�̗����鑬�x
		const float DownSpeed = 25.0f;

		mVelocity.y = -DownSpeed;
	}

	if (mPosition.y <= mEndPos.y)
	{
		mVelocity.y = 0.0f;
	}

	if (mPlayer->GetRespawnFlag())
	{
		mPosition = mInitPos;
		mVelocity.y = 0.0f;
	}

	// ��ɍ��W�ɑ��x�𑫂�
	mPosition += mVelocity;

	SetPosition(mPosition);
}