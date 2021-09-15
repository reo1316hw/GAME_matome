/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn	   �R���X�g���N�^
@param _pos �K���X���̍��W
@param _size �K���X���̃T�C�Y
@param _objectTag �K���X���̃^�O
@param _sceneTag �V�[���̃^�O
@param _playerPtr �v���C���[�̃|�C���^
*/
Glass::Glass(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag,const SceneBase::Scene _sceneTag, Player* _playerPtr) :
	GameObject(_sceneTag,_objectTag)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);
	mInitPos = _pos;

	mDownCount = 0;

	//��������Glass�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mInvisibleMeshComponent = new InvisibleMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mInvisibleMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));

	// �����蔻��
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_gpmeshName);
	mBoxcollider = new BoxCollider(this, ColliderTag::glassTag, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());

	mPlayer = _playerPtr;
}

/*
@fn		�K���X���̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void Glass::UpdateGameObject(float _deltaTime)
{
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

	if (mDownCount >= 15)
	{
		mVelocity.y = -DOWN_SPEED;
	}

	// ��ɍ��W�ɑ��x�𑫂�
	mPosition += mVelocity;

	SetPosition(mPosition);
}

/*
@fn		�K���X�����q�b�g�������̏���
@param	_hitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
*/
void Glass::OnCollision(const GameObject& _hitObject)
{
	mHitFlag = true;
}
