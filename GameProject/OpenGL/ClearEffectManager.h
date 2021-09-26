/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class RippleClearEffect;
class Player;

/*
@brief �N���A�G�t�F�N�g�̕���
*/
enum DirectionClearEffect
{
	eLeftUnderClear = 0,
	eRightUpClear = 1,
	eLeftUpClear = 2,
	eRightUnderClear = 3,
};

class ClearEffectManager : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	@param _playerPtr �v���C���[�̃|�C���^
	*/
	ClearEffectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~ClearEffectManager() {};

	/*
	@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn ���q�̃N���A�G�t�F�N�g����
	*/
	void CreateParticleClearEffect();

	/*
	@fn �g��̃N���A�G�t�F�N�g����
	*/
	void CreateRippleClearEffect();

	/*
	@fn ���x�����߂�
	*/
	void DecideVelocity();

	//�Q�[���I�u�W�F�N�g�N���X�̃|�C���^
	GameObject* mOwner;
	//�p�[�e�B�N���̏��
	ParticleState	 mState;
	//�V�[���̃^�O
	SceneBase::Scene mSceneTag;
	//�A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	Tag				 mTag;
	//�`�F�b�N�|�C���g�G�t�F�N�g
	RippleClearEffect* mRippleClearEffect;
	//�v���C���[�̃|�C���^
	Player* mPlayer;

	//�N���A�G�t�F�N�g����x�����������邽�߂̃t���O
	bool OneCreateClearFlag;
	//�p�x
	float mAngle;

	//��������^�C�~���O�̃J�E���g
	int mCreateTimingCount;
	//�������������J�E���g
	int mCreateCount;
};