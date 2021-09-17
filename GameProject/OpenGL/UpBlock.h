/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class Player;

class UpBlock : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos ��ړ��u���b�N�̍��W
	@param	_Size ��ړ��u���b�N�̃T�C�Y
	@param	_ObjectTag ��ړ��u���b�N�̃^�O
	@param	_SceneTag �V�[���̃^�O
	@param _playerPtr �v���C���[�̃|�C���^
	*/
	UpBlock(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~UpBlock() {};

	/*
	@fn		��ړ��u���b�N�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// �v���C���[�̃|�C���^
	Player* mPlayer;
};