/*
@brief	�v���v���Z�b�T
*/
#pragma once

/*
@brief	�C���N���[�h
*/

class OperationExplanationBoard : public ParticleEffectBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_pos ������@�p�l���̍��W
	@param	_vel ������@�p�l���̑��x
	@param	_objectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_sceneTag �V�[���̃^�O
	*/
	OperationExplanationBoard(const Vector3& _pos, const Vector3& _vel, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~OperationExplanationBoard() {};

private:
};

