/*
@brief �v���v���Z�b�T
*/
#pragma once

class VerticalMoveGroundExplanationBoard : public ParticleEffectBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �c�ړ����̐����p�l���̍��W
	@param	_Vel �c�ړ����̐����p�l���̑��x
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	VerticalMoveGroundExplanationBoard(const Vector3& _Pos, const Vector3& _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~VerticalMoveGroundExplanationBoard() {};

	/*
	@fn		�c�ړ����̐����p�l���̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override {};

private:

};

