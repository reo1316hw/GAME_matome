/*
@brief �v���v���Z�b�T
*/
#pragma once

class GoalLineRoot
{
public:

	/*
	@fn    �R���X�g���N�^
	@param _TopLeftOrigin ����̌��_
	@param	_SceneTag �V�[���̃^�O
	@param _playerPtr �v���C���[�̃|�C���^
	*/
	GoalLineRoot(const Vector3& _TopLeftOrigin, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
    @fn �f�X�g���N�^
    */
	~GoalLineRoot() {};

private:

	
	/*
	@fn    �e�S�[�����C���̑��x���w��
	@param _Quantity ��
	*/
	void SpecifyVel(const int _Quantity);
	
	/*
	@fn    �e�S�[�����C���̍��W���w��
	@param _Quantity ��
	*/
	void SpecifyPos(const int _Quantity);
	
	/*
	@fn    �e�S�[�����C���̑��x��␳
	@param _Quantity ��
	*/
	void CorrectVel(const int _Quantity);
	
	/*
	@fn   �e�S�[�����C���̃e�N�X�`���f�[�^���w��
	@param _Quantity ��
	*/
	void SpecifyTextureName(const int _Quantity);

	//�����ɔz�u����Ă���S�[�����C���̐�
	const int LeftNum;

	//�S�[�����C���̃|�C���^
	GoalLine* mGoalLine;

	//�e�N�X�`���f�[�^�̃p�X
	std::string mTextureName;

	//���W
	Vector3 mPos;
	//���x
	Vector3 mVel;
public://�Q�b�^�[�Z�b�^�[

	/*
	@return ���W
	*/
	Vector3 GetPos() { return mPos; };
};