/*
@brief	�v���v���Z�b�T
*/
#pragma once

/*
@brief	�C���N���[�h
*/

// �O���錾
class ClearEffect;
class Player;

class ClearEffectManager : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_objectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_sceneTag �V�[���̃^�O
	@param _playerPtr �v���C���[�̃|�C���^
	*/
	ClearEffectManager(const Tag& _objectTag, SceneBase::Scene _sceneTag, Player* _playerPtr);

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
	ClearEffect* mClearEffect;
	//�v���C���[�̃|�C���^
	Player* mPlayer;

	//�N���A�G�t�F�N�g����x�����������邽�߂̃t���O
	bool			 OneCreateClearFlag;
};