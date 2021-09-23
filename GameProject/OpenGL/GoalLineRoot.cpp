/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn    �R���X�g���N�^
@param _TopLeftOrigin ����̌��_
@param _playerPtr �v���C���[�̃|�C���^
*/
GoalLineRoot::GoalLineRoot(const Vector3& _TopLeftOrigin, Player* _playerPtr)
: mGoalLine(nullptr)
, mTextureName("0")
, mPos(_TopLeftOrigin)
, mVel(Vector3::sZERO)
{
	//�S�[�����C������
	for (int i = 0; i < 22; i++)
	{
		mPos = _TopLeftOrigin;

		//�e�S�[�����C���̑��x���w��
		SpecifyVel(i);
		//�e�S�[�����C���̍��W���w��
		SpecifyPos(i);
		//�e�S�[�����C���̃e�N�X�`���f�[�^���w��
		SpecifyTextureName(i);

		mGoalLine = new GoalLine(mPos, mVel, mTextureName, Tag::eOtherTag, SceneBase::Scene::eTutorial, _playerPtr);
	}
}

GoalLineRoot::~GoalLineRoot()
{
	delete mGoalLine;
}

/*
@fn    �e�S�[�����C���̑��x���w��
@param _Quantity ��
*/
void GoalLineRoot::SpecifyVel(const int _Quantity)
{
	//����(���S�܂�)�ɔz�u����Ă���S�[�����C���̑��x�w��
	if (_Quantity < 12)
	{
		mVel.y = 2.0f + (0.1f * _Quantity);
	}
	//�E��(���S�܂܂Ȃ�)�ɔz�u����Ă���S�[�����C���̑��x�w��
	else
	{
		mVel.y = 4.0f - (0.1f * _Quantity);
	}
}

/*
@fn    �e�S�[�����C���̍��W���w��
@param _Quantity ��
*/
void GoalLineRoot::SpecifyPos(const int _Quantity)
{
	//��i�̍��W�w��
	if (_Quantity % 2 == 0)
	{
		mPos.x += _Quantity * 50.0f;
	}
	//���i�̍��W�w��
	else if (_Quantity % 2 == 1)
	{
		mPos.x += _Quantity * 50.0f - 50.0f;
		mPos.y -= 100.0f;

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
	//���i�Ə�i�ő��x�𓯂��ɂ��邽�߂ɕ␳
	if (_Quantity < 12)
	{
		mVel.y -= 0.1f;
	}
	else
	{
		mVel.y += 0.1f;
	}
}

/*
@fn   �e�S�[�����C���̃e�N�X�`���f�[�^���w��
@param _Quantity ��
*/
void GoalLineRoot::SpecifyTextureName(const int _Quantity)
{
	switch (_Quantity % 4)
	{
	case 0:
		mTextureName = "Assets/heart.png";
		break;
	case 1:
		mTextureName = "Assets/checkpoint_stage01.png";
		break;
	case 2:
		mTextureName = "Assets/checkpoint_stage01.png";
		break;
	case 3:
		mTextureName = "Assets/heart.png";
		break;
	}
}
