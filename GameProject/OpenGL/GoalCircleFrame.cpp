/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �S�[���~�̘g�̍��W
@param	_Size �S�[���~�̘g�̃T�C�Y
@param	_ObjectTag �S�[���~�̘g�̃^�O
@param	_SceneTag �V�[���̃^�O
*/
GoalCircleFrame::GoalCircleFrame(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_SceneTag, _ObjectTag)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;

	//��������GoalBlock�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	//��]����
	float radian = Math::ToRadians(270);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::sUNIT_X, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}