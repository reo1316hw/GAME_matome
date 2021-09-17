/*
@brief �v���v���Z�b�T
*/
#pragma once

class CheckpointBoard : public ParticleEffectBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �`�F�b�N�|�C���g�{�[�h�̍��W
	@param	_Vel �`�F�b�N�|�C���g�{�[�h������@�p�l���̑��x
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	CheckpointBoard(const Vector3& _Pos, const Vector3& _Vel, const std::string& _ParticleFileName ,const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~CheckpointBoard() {};

	/*
	@fn		������@�p�l���̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override {};

private:

	AABB mCehckpointBoardAABB;
};