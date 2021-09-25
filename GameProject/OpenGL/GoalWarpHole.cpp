/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �S�[�����|�v�z�[���̍��W
@param	_Size �S�[�����|�v�z�[���̃T�C�Y
@param	_ObjectTag �S�[�����|�v�z�[���̃^�O
@param	_SceneTag �V�[���̃^�O
@param  _playerPtr �v���C���[�̃|�C���^
*/
GoalWarpHole::GoalWarpHole(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
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

	//���g�̃|�C���^���v���C���[�N���X�ɐݒ�
	_playerPtr->SetGoalWarpHolePtr(this);
}