#pragma once
#include "AttackBase.h"

/*
 @file AttackPlayerThird.h
 @brief �v���C���[�̃R���{3�i��
	*/
class AttackPlayerThird :
	public AttackBase
{
public:
	AttackPlayerThird();
	~AttackPlayerThird();

	void Attack(const Vector3& _ownerPosition,const float& _directiron)override;
};

