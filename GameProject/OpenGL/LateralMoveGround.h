/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class Player;

class LateralMoveGround : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos ���ړ����̍��W
	@param	_Size ���ړ����̃T�C�Y
	@param	_ObjectTag ���ړ����̃^�O
	@param	_SceneTag �V�[���̃^�O
	@param _distance ���ړ����̈ړ����鋗��
    @param _playerPtr �v���C���[�̃|�C���^
	*/
	LateralMoveGround(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, const float _Distance, Player* _playerPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~LateralMoveGround() {};

	/*
	@fn		���ړ����̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	static Vector3 mSendVel;

	// �v���C���[�̃|�C���^
	Player* mPlayer;

	//���]�t���O
	bool mReversFlag;

public://�Q�b�^�[�Z�b�^�[
	
	Vector3 GetVelocity() { return mSendVel; };
};