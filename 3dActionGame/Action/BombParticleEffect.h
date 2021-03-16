#pragma once
#include "ParticleEffectBase.h"

/*
@file BombParticleEffect.h
@brief �n�ʂƂ̏Փ˔�����s���A���˂���悤�ȋ������B���G�t�F�N�g
*/
class BombParticleEffect :
	public ParticleEffectBase
{
public:
	/*
	@param _pos ���W
	@param _velocity �ړ���
	*/
	BombParticleEffect(const Vector3& _pos, const Vector3& _velocity);
	~BombParticleEffect();
	/*
	@fn ��ʂ��Î~���Ă���Ƃ��Ɏc�葱���Ȃ��悤�J�E���g�_�E���𑱂���
	*/
	void PausingUpdateGameObject()override;
private:
	/*
	@fn �n�ʂƏՓ˂����Ƃ���velocity.y�𔽓]����velocity.x������������
	*/
	void OnTriggerEnter(ColliderComponent* colliderPair) override;
	/*
	@fn �d�͂𔽉f������
	*/
	void UpdateParticleObject(float _deltaTime)override;
	ColliderComponent* col;
};

