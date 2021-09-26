/*
@brief �v���v���Z�b�T
*/
#pragma once

class RippleClearEffect : public ParticleEffectBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �g��̃N���A�G�t�F�N�g�̐����ꏊ
	@param	_Vel �g��̃N���A�G�t�F�N�g�̑��x
	@param  _Color �g��̃N���A�G�t�F�N�g�̃J���[�l
	@param  _Scale �X�P�[���l
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	RippleClearEffect(const Vector3 _Pos, const Vector3 _Vel, const Vector3 _Color, const float _Scale, const Tag& _ObjectTag , const SceneBase::Scene _SceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~RippleClearEffect() {};

	/*
	@fn	�N���A�G�t�F�N�g�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
};

