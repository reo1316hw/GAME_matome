/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class CheckpointEffect;
class Player;

/*
@brief �`�F�b�N�|�C���g�G�t�F�N�g�̕���
*/
enum DirectionCheckpointEffect
{
	eRightCheckpoint = 0,
	eFrontCheckpoint = 1,
	eLeftCheckpoint = 2,
	eBackCheckpoint = 3,
	eRightFrontCheckpoint = 4,
	eLeftBackCheckpoint = 5,
	eRightBackCheckpoint = 6,
	eLeftFrontCheckpoint = 7
};

class CheckpointEffectManager : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	@param _playerPtr �v���C���[�̃|�C���^
	*/
	CheckpointEffectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~CheckpointEffectManager() {};

	/*
	@fn		�G�t�F�N�g�}�l�[�W���[�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
    @fn    ���x�����߂�
    @param _Quantity ��
    */
	void DecideVelocity(const int _Quantity);

	//�Q�[���I�u�W�F�N�g�N���X�̃|�C���^
	GameObject* mOwner;
	//�p�[�e�B�N���̏��
	ParticleState	 mState;
	//�V�[���̃^�O
	SceneBase::Scene mSceneTag;
	//�A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	Tag				 mTag;
	//�`�F�b�N�|�C���g�G�t�F�N�g
	CheckpointEffect* mCheckpointEffect;
	//�v���C���[�̃|�C���^
	Player* mPlayer;
};

