/*
@brief �v���v���Z�b�T
*/
#pragma once

class AerialBlock : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �󒆃u���b�N�̍��W
	@param	_Size �󒆃u���b�N�̃T�C�Y
	@param	_ObjectTag �󒆃u���b�N�̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	AerialBlock(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~AerialBlock() {};

private:
};