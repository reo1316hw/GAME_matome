/*
@brief �v���v���Z�b�T
*/
#pragma once

class GoalWarpBorard : public ParticleEffectBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �S�[�����[�v�̍��W
	@param	_Vel �S�[�����[�v�̑��x
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	GoalWarpBorard(const Vector3& _Pos, const Vector3& _Vel, const std::string& _ParticleFileName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~GoalWarpBorard() {};

	/*
	@fn		�S�[�����[�v�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	//�p�x
	float mAngle;
};