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
	@param _playerPtr �v���C���[�̃|�C���^
	*/
	GoalLineRoot(const Vector3& _TopLeftOrigin, Player* _playerPtr);

	/*
    @fn �f�X�g���N�^
    */
	~GoalLineRoot();

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

	//�S�[�����C���̃|�C���^
	GoalLine* mGoalLine;

	//�e�N�X�`���f�[�^�̃p�X
	std::string mTextureName;

	//���W
	Vector3 mPos;
	//���x
	Vector3 mVel;
};