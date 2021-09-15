/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn	   �R���X�g���N�^
@param _pos �����u���b�N�̍��W
@param _size �����u���b�N�̃T�C�Y
@param _objectTag �����u���b�N�̃^�O
@param _sceneTag �V�[���̃^�O
@param _playerPtr �v���C���[�̃|�C���^
*/
DownBlock::DownBlock(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag, Player* _playerPtr)
	: GameObject(_sceneTag, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);
	mInitPos = _pos;

	mEndPos = Vector3(_pos.x, _pos.y - 1600.0f, _pos.z);

	//��������DownBlock�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));

	// �����蔻��
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_gpmeshName);
	mBoxcollider = new BoxCollider(this, ColliderTag::downBlockTag, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());

	mPlayer = _playerPtr;
}

/*
@fn		�����u���b�N�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void DownBlock::UpdateGameObject(float _deltaTime)
{
	Vector3 playerPos = mPlayer->GetPosition();

	if (playerPos.z >= mPosition.z - 3000.0f)
	{
		mVelocity.y = -DOWN_SPEED;
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