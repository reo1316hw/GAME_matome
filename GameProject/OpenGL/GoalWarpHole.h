/*
@brief �v���v���Z�b�T
*/
#pragma once

class GoalWarpHole : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �S�[�����|�v�z�[���̍��W
	@param	_Size �S�[�����|�v�z�[���̃T�C�Y
	@param	_ObjectTag �S�[�����|�v�z�[���̃^�O
	@param	_SceneTag �V�[���̃^�O
	@param  _playerPtr �v���C���[�̃|�C���^
	*/
	GoalWarpHole(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~GoalWarpHole() {};

private:
};

