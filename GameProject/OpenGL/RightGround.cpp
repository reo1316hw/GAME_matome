/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_pos 1�}�X�E�ړ����̍��W
@param	_size 1�}�X�E�ړ����̃T�C�Y
@param	_objectTag 1�}�X�E�ړ����̃^�O
@param	_sceneTag �V�[���̃^�O
@param _playerPtr �v���C���[�̃|�C���^
*/
RightGround::RightGround(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag, Player* _playerPtr)
	: GameObject(_sceneTag, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);
	mInitPos = _pos;

	mEndPos = Vector3(_pos.x + 200, _pos.y, _pos.z);

	//��������RightOneBlock�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));

	// �����蔻��
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_gpmeshName);
	mBoxcollider = new BoxCollider(this, ColliderTag::rightGroundTag, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());

	mOriginalPosFlag = false;

	mPlayer = _playerPtr;
}

/*
@fn		1�}�X�E�ړ����̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void RightGround::UpdateGameObject(float _deltaTime)
{
	Vector3 playerPos = mPlayer->GetPosition();

	if (playerPos.z >= mPosition.z - 600.0f)
	{
		mVelocity.x = RIGHT_SPEED;
	}

	if (mPosition.x >= mEndPos.x)
	{
		mVelocity.x = 0;
	}

	if (mInitPos.x < mPosition.x)
	{
		mOriginalPosFlag = true;
	}

	if (mPlayer->GetDeathFlag())
	{
		mVelocity.x = 0;
		mOriginalPosFlag = false;
	}

	if (mOriginalPosFlag)
	{
		if (mPlayer->GetRespawnFlag())
		{
			mVelocity.x = 0;
			mPosition.x = mInitPos.x;
			mOriginalPosFlag = false;
		}
	}

	// ��ɍ��W�ɑ��x�𑫂�
	mPosition += mVelocity;

	SetPosition(mPosition);
}
