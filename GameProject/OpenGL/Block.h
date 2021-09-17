/*
@brief �v���v���Z�b�T
*/
#pragma once

class Block : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos ��Q���̍��W
	@param	_Size ��Q���̃T�C�Y
	@param	_ObjectTag ��Q���̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	Block(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~Block() {};

private:
};