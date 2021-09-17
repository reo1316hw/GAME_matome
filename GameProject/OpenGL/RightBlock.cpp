/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �E�ړ��u���b�N�̍��W
@param	_Size �E�ړ��u���b�N�̃T�C�Y
@param	_ObjectTag �E�ړ��u���b�N�̃^�O
@param	_SceneTag �V�[���̃^�O
@param _playerPtr �v���C���[�̃|�C���^
*/
RightBlock::RightBlock(const Vector3& _Pos, const Vector3& _Size, const float _AddEndPosX, const std::string _GpmeshName, const Tag& _ObjectTag, const ColliderTag& _ColliderTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
	: GameObject(_SceneTag, _ObjectTag)
	, mElapseTime(0.0f)
	, mDifferencePos(0.0f)
	, mStart(0.0f)
	, mShakeFlag(false)
	, mInversionPos(Vector3::sZERO)
{
	// ���]����n�_�܂ł̋���
	const float Distance = 60.0f;

	//GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;

	mEndPos = Vector3(_Pos.x + _AddEndPosX, _Pos.y, _Pos.z);
	mInversionPos = Vector3(_Pos.x + Distance, _Pos.y, _Pos.z);

	//��������RightBlock�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmMesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	// �����蔻��
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_GpmeshName);
	mBoxcollider = new BoxCollider(this, _ColliderTag, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());

	mOriginalPosFlag = false;

	mPlayer = _playerPtr;
}

/*
@fn		�E�ړ��u���b�N�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void RightBlock::UpdateGameObject(float _deltaTime)
{
	//�v���C���[�̍��W
	Vector3 playerPos = mPlayer->GetPosition();
	//����
	float distance = 2040.0f;
	//�\�m������J�n���邽�߂�z���W
	float ShakeZPos = mPosition.z - distance;

	//////////////////////////////////////
	//�\�m���쏈��
	if (playerPos.z >= ShakeZPos)
	{
		mShakeFlag = true;
	}

	if (mShakeFlag)
	{
		if (mPosition.x >= mInversionPos.x)
		{
			mReversFlag = true;
		}
		else if (mPosition.x <= mInitPos.x)
		{
			mReversFlag = false;
		}

		
		//�E�ړ��u���b�N�̉E�Ɉړ����鑬�x
		const float RightSpeed = 20.0f;

		if (mReversFlag == true)
		{
			mVelocity.x = -RightSpeed;
		}
		else if (mReversFlag == false)
		{
			mVelocity.x = RightSpeed;
		}
	}
	/////////////////////////////////////////

	distance = 1800.0f;
	//�����n�߂邽�߂�z���W
	const float MoveZPos = mPosition.z - distance;

	if (playerPos.z >= MoveZPos)
	{
		//�S�̂̎���
		const float TotalTime = 1.0f;

		mShakeFlag = false;
		mElapseTime += _deltaTime;
		mDifferencePos = mEndPos.x - mInitPos.x;
		mVelocity.x = Quartic::EaseIn(mElapseTime, mStart , mDifferencePos, TotalTime) * 0.02f;
	}

	if (mInitPos.x < mPosition.x)
	{
		mOriginalPosFlag = true;
	}

	if (mPosition.x >= mEndPos.x)
	{
		mVelocity.x = 0.0f;
	}

	if (mPlayer->GetDeathFlag())
	{
		mElapseTime = 0.0f;
		mVelocity.x = 0.0f;
		mOriginalPosFlag = false;
	}

	if (mOriginalPosFlag)
	{
		if (mPlayer->GetRespawnFlag())
		{
			mElapseTime = 0.0f;
			mVelocity.x = 0.0f;
			mPosition = mInitPos;
			mShakeFlag = false;
			mOriginalPosFlag = false;
		}
	}

	// ��ɍ��W�ɑ��x�𑫂�
	mPosition += mVelocity;

	SetPosition(mPosition);
}