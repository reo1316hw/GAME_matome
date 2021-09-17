/*
@brief �v���v���Z�b�T
*/
#pragma once

class SandEffect :public ParticleEffectBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos ���ڂ���̍��W
	@param	_Vel ���ڂ���̑��x
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	SandEffect(const Vector3 _Pos, const Vector3 _Vel, const SceneBase::Scene _SceneTag,const Tag& _ObjectTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~SandEffect() {};

	/*
	@fn		���ڂ���̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
};

