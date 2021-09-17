/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class Player;

class RightGround : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos 1�}�X�E�ړ����̍��W
	@param	_Size 1�}�X�E�ړ����̃T�C�Y
	@param	_ObjectTag 1�}�X�E�ړ����̃^�O
	@param	_SceneTag �V�[���̃^�O
	@param _playerPtr �v���C���[�̃|�C���^
	*/
	RightGround(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~RightGround() {};

	/*
	@fn		1�}�X�E�ړ����̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// �v���C���[�̃|�C���^
	Player* mPlayer;
};