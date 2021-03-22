#include "GroundCollider.h"
#include "SphereCollider.h"

GroundCollider::GroundCollider(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, objectTag)
	, groundSphere(Vector3::Zero, 0.0f)
{
	sphereCollider = new SphereCollider(this, ColliderComponent::playerTag, GetOnCollisionFunc());
	Sphere sphere = { Vector3::Zero,5.0f };
	sphereCollider->SetObjectSphere(sphere);
}

GroundCollider::~GroundCollider()
{
}

void GroundCollider::UpdateGameObject(float _deltaTime)
{
}

void GroundCollider::OnCollision(const GameObject& _hitObject)
{
}
