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
	@param	_pos 1�}�X�E�ړ����̍��W
	@param	_size 1�}�X�E�ړ����̃T�C�Y
	@param	_objectTag 1�}�X�E�ړ����̃^�O
	@param	_sceneTag �V�[���̃^�O
	@param _playerPtr �v���C���[�̃|�C���^
	*/
	RightGround(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag, Player* _playerPtr);

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

	//1�}�X�E�ړ����̉E�Ɉړ����鑬�x
	const float RIGHT_SPEED = 10.0f;
};