/*
@brief �v���v���Z�b�T
*/
#pragma once

class Ground : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos ���̍��W
	@param	_Size ���̃T�C�Y
	@param	_ObjectTag ���̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	Ground(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~Ground() {};

private:

};