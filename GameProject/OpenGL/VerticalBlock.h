/*
@brief �v���v���Z�b�T
*/
#pragma once

class VerticalBlock : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �c����Q���̍��W
	@param	_Size �c����Q���̃T�C�Y
	@param	_ObjectTag �c����Q���̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	VerticalBlock(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~VerticalBlock() {};

private:
};