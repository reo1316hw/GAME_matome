#pragma once
#include "AttackBase.h"

/*
 @file AttackPlayerTwice.h
 @brief �v���C���[�̃R���{2�i��
	*/
class AttackPlayerTwice final :
	public AttackBase
{
public:
	AttackPlayerTwice();
	~AttackPlayerTwice();

	void Attack(const Vector3& _ownerPosition,const float& _directiron)override;
};

