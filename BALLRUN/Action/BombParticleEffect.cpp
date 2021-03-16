#include "BombParticleEffect.h"
#include "ColliderComponent.h"
#include "PhysicsWorld.h"

/*
@param _pos ���W
@param _velocity �ړ���
*/
BombParticleEffect::BombParticleEffect(const Vector3& _pos, const Vector3& _velocity) :
	ParticleEffectBase(_pos, _velocity, 70, "Assets/Image/16.png")
{
	tag = (Tag::ParticleEffectTag);
	 col = new ColliderComponent(this, 100, Vector3(40, 40, 40), gameObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);

}


BombParticleEffect::~BombParticleEffect()
{
}

/*
@fn ��ʂ��Î~���Ă���Ƃ��Ɏc�葱���Ȃ��悤�J�E���g�_�E���𑱂���
*/
void BombParticleEffect::PausingUpdateGameObject()
{
	LifeCountDown();
	col->SetCollidedCamera();
}

/*
@fn �n�ʂƏՓ˂����Ƃ���velocity.y�𔽓]����velocity.x������������
*/
void BombParticleEffect::OnTriggerEnter(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::GroundTag)
	{
		velocity.y *= -1;
		velocity = velocity * 0.8f;
	}
}

/*
@fn �d�͂𔽉f������
*/
void BombParticleEffect::UpdateParticleObject(float _deltaTime)
{
	velocity.y -= 100 * _deltaTime;
	LifeCountDown();
}
