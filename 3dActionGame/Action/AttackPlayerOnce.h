#pragma once
#include "AttackBase.h"

/*
 @file AttackPlayerOnce.h
 @brief �v���C���[�̃R���{1�i��
 ���C�X���΂��N���X�Btwice��Third�𓝈ꂷ�ׂ��B
	*/
class AttackPlayerOnce :
	public AttackBase
{
public:
	AttackPlayerOnce();
	~AttackPlayerOnce();
	void Attack(const Vector3& _ownerPosition,const float& _directiron)override;
};

