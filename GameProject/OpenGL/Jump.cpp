/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �W�����v���̍��W
@param	_Size �W�����v���̃T�C�Y
@param	_ObjectTag �W�����v���̃^�O
@param	_SceneTag �V�[���̃^�O
*/
Jump::Jump(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr) :
	GameObject(_SceneTag, _ObjectTag)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;

	degree = 0.0f;
	mVelocity = Vector3::sZERO;

	//��������Jump�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	//��`�����蔻��
	const AABB Box = AABB(Vector3(-1.0f, -1.0f, -1.0f), Vector3(1.0f, 1.0f, 1.0f));

	mBoxcollider = new BoxCollider(this, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(Box);

	mPlayer = _playerPtr;
}

/*
@fn		�W�����v���̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void Jump::UpdateGameObject(float _deltaTime)
{
	if (mPlayer->GetRespawnFlag())
	{
		mHitFlag = false;
		mVelocity = Vector3::sZERO;
		mPosition = mInitPos;
		degree = 0.0f;
	}

	if (mHitFlag)
	{
		// sin�J�[�u
		mVelocity.y = sinf(degree) * 8.0f;
		mVelocity.z = sinf(degree) * 8.0f;
		degree += 0.2f;

		if (degree >= 6.5f)
		{
			degree = 0.0f;
			mVelocity.y = 0.0f;
			mVelocity.z = 0.0f;
			mHitFlag = false;
		}
	}

	// ��ɍ��W�ɑ��x�𑫂�
	mPosition += mVelocity;

	SetPosition(mPosition);
}

/*
@fn		�W�����v�����q�b�g�������̏���
@param	_HitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
*/
void Jump::OnCollision(const GameObject& _HitObject)
{
	mHitFlag = true;
}