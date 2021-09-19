/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class Player;

class LeftBlock : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos ���ړ����̍��W
	@param	_Size ���ړ����̃T�C�Y
	@param	_ObjectTag ���ړ����̃^�O
	@param	_SceneTag �V�[���̃^�O
	@param _playerPtr �v���C���[�̃|�C���^
	*/
	LeftBlock(const Vector3& _Pos, const Vector3& _Size, const float _AddPosX, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~LeftBlock() {};

	/*
	@fn		���ړ����̃A�b�v�f�[�g
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