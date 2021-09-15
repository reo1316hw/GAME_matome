/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class CheckpointEffect;
class Player;

class CheckpointEffectManager : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_objectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_sceneTag �V�[���̃^�O
	@param _playerPtr �v���C���[�̃|�C���^
	*/
	CheckpointEffectManager(const Tag& _objectTag, SceneBase::Scene _sceneTag, Player* _playerPtr);

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
    @param _quantity ��
    */
	void DecideVelocity(const int _quantity);

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

	//���x
	const float SPEED = 10.0f;
	//����
	const float DIRECTION = 1.0f;
};

