#include "Goal.h"

Goal::Goal(const Vector3& _pos, const Vector3& _velocity, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: ParticleEffectBase(_pos, _velocity, 0, "Assets/Goal.png", _sceneTag, _objectTag)
{
	mScale = 1000.0f;
	mAlpha = 0.5f;
	particle->SetScale(mScale);
	particle->SetAlpha(mAlpha);
	particle->SetColor(Vector3(1.0f, 1.0f, 1.0f));
}

void Goal::UpdateGameObject(float _deltaTime)
{
	/*ParticleEffectBase::LifeCountDown();

	if (lifeCount >= 0)
	{
		position += velocity * 10.0f;

		mScale += 5.0f;
		mAlpha -= 0.05f;
		particle->SetScale(mScale);
		particle->SetAlpha(mAlpha);
		SetPosition(position);
	}

	if (lifeCount <= 0)
	{
		state = State::Dead;
	}*/
}
