/*
@brief �v���v���Z�b�T
*/
#pragma once

class ClearEffect : public ParticleEffectBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �N���A�G�t�F�N�g�̐����ꏊ
	@param	_Vel �N���A�G�t�F�N�g�̑��x
	@param  _Color �N���A�G�t�F�N�g�̃J���[�l
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	ClearEffect(const Vector3 _Pos, const Vector3 _Vel, const Vector3 _Color, const Tag& _ObjectTag , const SceneBase::Scene _SceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~ClearEffect() {};

	/*
	@fn	�N���A�G�t�F�N�g�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
};

