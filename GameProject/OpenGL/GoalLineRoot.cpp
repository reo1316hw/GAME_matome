/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn    �R���X�g���N�^
@param _TopLeftOrigin ����̌��_
@param	_SceneTag �V�[���̃^�O
@param _playerPtr �v���C���[�̃|�C���^
*/
GoalLineRoot::GoalLineRoot(const Vector3& _TopLeftOrigin, const SceneBase::Scene _SceneTag, Player* _playerPtr)
: mGoalLine(nullptr)
, mTextureName("0")
, mPos(_TopLeftOrigin)
, mVel(Vector3::sZERO)
, LeftNum(12)
{
	//�S�[�����C���̃I�u�W�F�N�g��
	const int GoalLineNum = 22;

	//�S�[�����C������
	for (int i = 0; i < GoalLineNum; i++)
	{
		mPos = _TopLeftOrigin;

		//�e�S�[�����C���̑��x���w��
		SpecifyVel(i);
		//�e�S�[�����C���̍��W���w��
		SpecifyPos(i);
		//�e�S�[�����C���̃e�N�X�`���f�[�^���w��
		SpecifyTextureName(i);

		mGoalLine = new GoalLine(mPos, mVel, mTextureName, Tag::eOtherTag, _SceneTag, _playerPtr);
	}
}

/*
@fn    �e�S�[�����C���̑��x���w��
@param _Quantity ��
*/
void GoalLineRoot::SpecifyVel(const int _Quantity)
{
	//�����̏����x
	const float LeftInitialVelocity = 2.0f;
	//�E���̏����x
	const float RightInitialVelocity = 4.0f;
	//�e�S�[�����C���ɒǉ����鑬�x
	float addVel = 0.1f * _Quantity;
	//�����ɔz�u����Ă���S�[�����C���̑��x
	float leftVel = 0.0f;
	//�E���ɔz�u����Ă���S�[�����C���̑��x
	float rightVel = 0.0f;

	//����(���S�܂�)�ɔz�u����Ă���S�[�����C���̑��x�w��
	if (_Quantity < LeftNum)
	{
		leftVel = LeftInitialVelocity + addVel;
		mVel.y = leftVel;
	}
	//�E��(���S�܂܂Ȃ�)�ɔz�u����Ă���S�[�����C���̑��x�w��
	else
	{
		rightVel = RightInitialVelocity - addVel;
		mVel.y = rightVel;
	}
}

/*
@fn    �e�S�[�����C���̍��W���w��
@param _Quantity ��
*/
void GoalLineRoot::SpecifyPos(const int _Quantity)
{
	//��̐�
	const int ColumnNum = 2;
	//�e�S�[�����C���ɒǉ�������W
	const float AddPos = 50.0f * _Quantity;
	//���i��X�������炷
	const float ShiftXPos = 50.0f;
	//���i��Y�������炷
	const float ShiftYPos = 100.0f;

	//��i�̍��W�w��
	if (_Quantity % ColumnNum == 0)
	{
		mPos.x += AddPos;
	}
	//���i�̍��W�w��
	else if (_Quantity % ColumnNum == 1)
	{
		mPos.x += AddPos - ShiftXPos;
		mPos.y -= ShiftYPos;

		//�e�S�[�����C���̑��x��␳
		CorrectVel(_Quantity);
	}
}

/*
@fn    �e�S�[�����C���̑��x��␳
@param _Quantity ��
*/
void GoalLineRoot::CorrectVel(const int _Quantity)
{
	//�␳�l
	const float CorrectionValue = 0.1f;

	//���i�Ə�i�ő��x�𓯂��ɂ��邽�߂ɕ␳
	if (_Quantity < LeftNum)
	{
		mVel.y -= CorrectionValue;
	}
	else
	{
		mVel.y += CorrectionValue;
	}
}

/*
@fn   �e�S�[�����C���̃e�N�X�`���f�[�^���w��
@param _Quantity ��
*/
void GoalLineRoot::SpecifyTextureName(const int _Quantity)
{
	//1�O���[�v�̒��̐�
	const int InGropeNum = 4;

	switch (_Quantity % InGropeNum)
	{
    //����
	case 0:
		mTextureName = "Assets/heart.png";
		break;
	//����
	case 1:
		mTextureName = "Assets/checkpoint_stage01.png";
		break;
	//�E��
	case 2:
		mTextureName = "Assets/checkpoint_stage01.png";
		break;
    //�E��
	case 3:
		mTextureName = "Assets/heart.png";
		break;
	}
}
