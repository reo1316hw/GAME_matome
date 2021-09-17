/*
@brief�v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class Player;
class InvisibleMeshComponent;

class Glass : public GameObject
{
public:

	/*
	@fn	   �R���X�g���N�^
	@param _Pos �K���X���̍��W
	@param _Size �K���X���̃T�C�Y
	@param _ObjectTag �K���X���̃^�O
	@param _SceneTag �V�[���̃^�O
	@param _playerPtr �v���C���[�̃|�C���^
	*/
	Glass(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~Glass() {};

	/*
	@fn		�K���X���̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	//�K���X���̃A���t�@�u�����h���b�V��
	InvisibleMeshComponent* mInvisibleMeshComponent;

	// �v���C���[�̃|�C���^
	Player* mPlayer;

	//������܂ł̃J�E���g
	int mDownCount;

	/*
	@fn		�K���X�����q�b�g�������̏���
	@param	_HitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
	*/
	void OnCollision(const GameObject& _HitObject)override;
};