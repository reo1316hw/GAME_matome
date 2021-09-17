/*
@brief �v���v���Z�b�T
*/
#pragma once

class GoalBlock : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �S�[�����̍��W
	@param	_Size �S�[�����̃T�C�Y
	@param	_ObjectTag �S�[�����̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	GoalBlock(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~GoalBlock() {};

private:

};