/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �󒆃u���b�N�̍��W
@param	_Size �󒆃u���b�N�̃T�C�Y
@param	_ObjectTag �󒆃u���b�N�̃^�O
@param	_SceneTag �V�[���̃^�O
*/
AerialBlock::AerialBlock(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_SceneTag, _ObjectTag)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;

	//��������AerialBlock�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	//�����蔻��
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_GpmeshName);
	mBoxcollider = new BoxCollider(this, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());
}