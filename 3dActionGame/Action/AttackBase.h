#pragma once
#include "Math.h"

/*
 @file AttackBase.h
 @brief �v���C���[�̍U�����N���X�BAttack���̊֐��ōU�����e�����肷��
	*/
class AttackBase abstract
{
public:
	AttackBase();
	~AttackBase();
	/*
	@fn �U�����e
	@param _ownerPosition �U���������W
	@param _directiron �U���������
	*/
	virtual void Attack(const Vector3& _ownerPosition,const float& _directiron) {};

protected:
	//�h���N���X�Ō��肷��l�B�h���N���X�̍U�����s�����ۂɃv���C���[�ɔ�������ړ��s����(�d��)
	float canNotActionTime;
	//�h���N���X�Ō��肷��l�B���̍U���ɔh��������P�\����(�R���{�P�\����)
	float waitTimeForNextAttack;
public://�Q�b�^�[�Z�b�^�[
	/*
	@return �U������̃A�N�V�������󂯕t���Ȃ����ԁB�d���B
	*/
	float GetCanNotActionTime() { return canNotActionTime; }
	/*
	@return �U�����玟�̍U���Ɍq���邱�Ƃ��ł��鎞�ԁB�R���{�P�\
	*/
	float GetWaitTimeForNextAttack() { return waitTimeForNextAttack; }
};

