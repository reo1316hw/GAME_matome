/*
@brief �v���v���Z�b�T
*/
#pragma once

class GoalCircleFrame : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �S�[���~�̘g�̍��W
	@param	_Size �S�[���~�̘g�̃T�C�Y
	@param	_ObjectTag �S�[���~�̘g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	GoalCircleFrame(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~GoalCircleFrame() {};

private:
};

