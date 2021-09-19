/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class Player;

class RightBlock : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �E�ړ��u���b�N�̍��W
	@param	_Size �E�ړ��u���b�N�̃T�C�Y
	@param	_ObjectTag �E�ړ��u���b�N�̃^�O
	@param	_SceneTag �V�[���̃^�O
    @param _playerPtr �v���C���[�̃|�C���^
	*/
	RightBlock(const Vector3& _Pos, const Vector3& _Size, const float _AddEndPosX, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~RightBlock() {};

	/*
	@fn		�E�ړ��u���b�N�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// �v���C���[�̃|�C���^
	Player* mPlayer;

	//���]������W
	Vector3 mInversionPos;

	//�h��邩
	bool mShakeFlag;
	//���]���邩
	bool mReversFlag;

	//����(�i�s�x)
	float mElapseTime;
	//�J�n�ƏI���̒l�̍���
	float mDifferencePos;
	//�J�n�̒l
	float mStart;
};