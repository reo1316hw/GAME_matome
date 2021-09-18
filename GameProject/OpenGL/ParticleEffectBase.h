/*
@file ParticleEffectBase.h
@brief ��莞�Ԃŏ�����A��ɃG�t�F�N�g�̊��N���X�Ƃ��Ďg�p�����N���X
*/

/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@enum	�p�[�e�B�N���̏��
*/
enum ParticleState
{
	//�A�N�e�B�u
	eParticleActive,
	//�����ɂ���
	eParticleDisable,
};

class ParticleEffectBase : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �G�t�F�N�g�̐����ꏊ
	@param	_Vel �G�t�F�N�g�̑��x
	@param	_LifeCount �G�t�F�N�g�̐�������
	@param	_ParticleFileName �摜�ւ̃A�h���X
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	@param	_Scale �摜�̊g��T�C�Y
	*/
	ParticleEffectBase(const Vector3& _Pos, const Vector3& _Vel, const int& _LifeCount, const std::string& _ParticleFileName, const SceneBase::Scene _SceneTag, const Tag& _ObjectTag,const float& _Scale = 10);

	/*
	@fn	�f�X�g���N�^
	*/
	virtual ~ParticleEffectBase() {};

	/*
	@fn		�h���N���X�̍X�V�֐����Ăэ��W�Ɉړ��ʂ𑫂�������
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

protected:

	/*
	@fn �������Ԃ��J�E���g�_�E������֐��B�h���N���X�ōX�V�֐������肵���ꍇ�����ɒǉ����邱�ƁB
	*/
	void LifeCountDown();

	//�p�[�e�B�N���̕`��N���X
	ParticleComponent*	mParticle;
	//�p�[�e�B�N���̏��
	ParticleState		mParticleState;

	//��������
	int					mLifeCount;

	//�A���t�@�l
	float				mAlpha;
	//�傫��
	float				mScale;
	//�����x
	float				mSpeed;

public:

	/*
	@param _flag ���]���s����
	*/
	void SetReverve(float _flag);
};
