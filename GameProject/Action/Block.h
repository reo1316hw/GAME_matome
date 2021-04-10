/*
@brief	�v���v���Z�b�T
*/
#pragma once

/*
@brief	�C���N���[�h
*/
#include "GameObject.h"

class Block : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_pos �Q�[���I�u�W�F�N�g�̍��W
	@param	_size �Q�[���I�u�W�F�N�g�̃T�C�Y
	@param	_objectTag �Q�[���I�u�W�F�N�g�̃^�O
	@param	_sceneTag �V�[���̃^�O
	*/
	Block(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~Block() {};

private:
};