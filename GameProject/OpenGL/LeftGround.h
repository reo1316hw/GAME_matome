/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class Player;

class LeftGround : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_pos 1�}�X���ړ����̍��W
	@param	_size 1�}�X���ړ����̃T�C�Y
	@param	_objectTag 1�}�X���ړ����̃^�O
	@param	_sceneTag �V�[���̃^�O
    @param _playerPtr �v���C���[�̃|�C���^
	*/
	LeftGround(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag, Player* _playerPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~LeftGround() {};

	/*
	@fn		1�}�X���ړ����̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// �v���C���[�̃|�C���^
	Player* mPlayer;

	//1�}�X���ړ����̍��Ɉړ����鑬�x
	const float LEFT_SPEED = 10.0f;
};