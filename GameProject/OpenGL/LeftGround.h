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
	@param	_Pos 1�}�X���ړ����̍��W
	@param	_Size 1�}�X���ړ����̃T�C�Y
	@param	_ObjectTag 1�}�X���ړ����̃^�O
	@param	_SceneTag �V�[���̃^�O
    @param _playerPtr �v���C���[�̃|�C���^
	*/
	LeftGround(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

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
};