#include "ClearEffect.h"
#include "Renderer.h"
#include "ParticleComponent.h"
#include "SceneBase.h"
#include "GameObject.h"

ClearEffect::ClearEffect(Vector3 _pos, Vector3 _vel, SceneBase::Scene _sceneTag, const Tag& _objectTag)
	:ParticleEffectBase(_pos, _vel, 30, "Assets/miniGlass.png", _sceneTag, _objectTag)
{
	mAlpha = 0.5f;
	mScale = 8.0f;
	particle->SetAlpha(mAlpha);
	particle->SetScale(mScale);
	particle->SetColor(Color::Yellow);
	particle->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM_ALPHA);
	speed = 1.0f;
}

void ClearEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	if (lifeCount > 0)
	{
		mAlpha -= 0.01f;
		mScale += 1.0f;
		particle->SetAlpha(mAlpha);
		particle->SetScale(mScale);
		velocity = velocity * speed;
		position = position + velocity;
		SetPosition(position);
	}

	if (lifeCount <= 0)
	{
		particle->SetVisible(false);
	}
}
