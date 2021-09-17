/*
@brief �C���N���[�h
*/
#include "pch.h"

Vector3 LateralMoveGround::mSendVel = Vector3::sZERO;

/*
@fn		�R���X�g���N�^
@param	_Pos ���ړ����̍��W
@param	_Size ���ړ����̃T�C�Y
@param	_ObjectTag ���ړ����̃^�O
@param	_SceneTag �V�[���̃^�O
@param _distance ���ړ����̈ړ����鋗��
@param _playerPtr �v���C���[�̃|�C���^
*/
LateralMoveGround::LateralMoveGround(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, const float _Distance, Player* _playerPtr)
	: GameObject(_SceneTag, _ObjectTag)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	// �����̍��W
	mInitPos = _Pos;

	// �ړ���̍��W
	mEndPos = Vector3(_Pos.x - _Distance, _Pos.y, _Pos.z) ;

	//��������LateralMoveGround�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	// �����蔻��
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_GpmeshName);
	mBoxcollider = new BoxCollider(this, ColliderTag::eLateralMoveGroundTag, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());

	// ���]�t���O
	mReversFlag = false;
	mOriginalPosFlag = false;

	mPlayer = _playerPtr;
}

/*
@fn		���ړ����̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void LateralMoveGround::UpdateGameObject(float _deltaTime)
{
	if (mInitPos.x != mPosition.x)
	{
		mOriginalPosFlag = true;
	}

	if (mPlayer->GetDeathFlag())
	{
		mVelocity.x = 0.0f;
		mOriginalPosFlag = false;
	}

	if (mOriginalPosFlag)
	{
		if (mPlayer->GetRespawnFlag())
		{
			mVelocity.x = 0.0f;
			mPosition = mInitPos;
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

	//���ړ�����Ƃ��̑��x
	const float MoveSpeed = 10.0f;

	if (mReversFlag == true )
	{
		mVelocity.x = MoveSpeed;
		
	}
	else if(mReversFlag == false)
	{
		mVelocity.x = -MoveSpeed;
	}

	mSendVel = mVelocity;
	mPosition += mVelocity;

	SetPosition(mPosition);
}