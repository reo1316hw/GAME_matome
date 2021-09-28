/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn	   �R���X�g���N�^
@param _Pos �K���X���̍��W
@param _Size �K���X���̃T�C�Y
@param _ObjectTag �K���X���̃^�O
@param _SceneTag �V�[���̃^�O
@param _playerPtr �v���C���[�̃|�C���^
*/
Glass::Glass(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag,const SceneBase::Scene _SceneTag, Player* _playerPtr) :
	GameObject(_SceneTag,_ObjectTag)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;

	mDownCount = 0;

	//��������Glass�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mInvisibleMeshComponent = new InvisibleMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mInvisibleMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	//��`�����蔻��
	const AABB Box = AABB(Vector3(-1.0f, -1.0f, -1.0f), Vector3(1.0f, 1.0f, 1.0f));

	mBoxcollider = new BoxCollider(this, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(Box);

	mPlayer = _playerPtr;
}

/*
@fn		�K���X���̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void Glass::UpdateGameObject(float _deltaTime)
{
	// ���Ƃ����߂̃J�E���g�̏���l
	const int LimitDownCount = 16;

	if (mPlayer->GetRespawnFlag())
	{
		mHitFlag = false;
		mDownCount = 0;
		mVelocity.y = 0.0f;
		mPosition = mInitPos;
	}

	if (mHitFlag)
	{
		mDownCount++;
	}

	// ���Ƃ����߂̃J�E���g������l�܂ŒB������K���X����������
	if (mDownCount >= LimitDownCount)
	{
		// ������X�s�[�h
		const float DownSpeed = 100.0f;

		mVelocity.y = -DownSpeed;
	}

	// ��ɍ��W�ɑ��x�𑫂�
	mPosition += mVelocity;

	SetPosition(mPosition);
}

/*
@fn		�K���X�����q�b�g�������̏���
@param	_HitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
*/
void Glass::OnCollision(const GameObject& _HitObject)
{
	mHitFlag = true;
}
