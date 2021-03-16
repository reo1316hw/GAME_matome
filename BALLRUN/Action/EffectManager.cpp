#include "EffectManager.h"
#include "SandEffect.h"
#include "DeathEffect.h"
#include "ClearEffect.h"
#include "Player.h"

EffectManager::EffectManager(GameObject* _owner, SceneBase::Scene _sceneTag, const Tag& _objectTag)
	:GameObject(_sceneTag, _objectTag)
{
	owner = _owner;
	state = ParticleState::PARTICLE_DISABLE;
	prePos = Vector3::Zero;
	sceneTag = _sceneTag;
	tag = _objectTag;

	angle = 0.0f;

	clearEffectFlag = false;
	deathEffectFlag = false;
}

void EffectManager::UpdateGameObject(float _deltaTime)
{
	if (prePos != owner->GetPosition())
	{
		state = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		state = ParticleState::PARTICLE_DISABLE;
	}

	if (player->GetClearFlag())
	{
		clearEffectFlag = true;

	}

	if (player->GetDeathFlag())
	{
		deathEffectFlag = true;
	}

	switch (state)
	{
	case PARTICLE_DISABLE:
		break;
	case PARTICLE_ACTIVE:

		++frameCount;
		Vector3 vel = Vector3(0.0f, 0.0f, 0.0f);
		position = owner->GetPosition();
		position.y -= 10.0f;
		position.z -= 20.0f;
		if (frameCount % 6 == 0)
		{

			vel = Vector3(0.0f, 0.0f, -1.0);
			sandEffect = new SandEffect(position, vel, sceneTag, tag);
			
		}		

		if (frameCount % 1 == 0)
		{
			if (deathEffectFlag)
			{
				for (int i = 0; i < 50; i++)
				{
					Vector3 randVel = Vector3(rand() % 100 + 1.0f, rand() % 100 + 1.0f, rand() % 100 + 1.0f);
					randVel.Normalize();

					if (i % 2 == 0)
					{
						randVel.x *= -1.0f;
						randVel.z *= -1.0f;
					}

					if (i % 5 == 0)
					{
						randVel.x *= -1.0f;
					}

					if (i % 3 == 0)
					{
						randVel.z *= -1.0f;
					}

					deathEffect = new DeathEffect(position, randVel, sceneTag, tag);
				}

				deathEffectFlag = false;

			}
			
			if (clearEffectFlag)
			{

				clearEffect = new ClearEffect(position, vel, sceneTag, tag);

				float x = 0.0f;
				float y = 0.0f;
				float x2 = 0.0f;
				float y2 = 0.0f;
				float x3 = 0.0f;
				float y3 = 0.0f;
				float x4 = 0.0f;
				float y4 = 0.0f;
				float x5 = 0.0f;
				float y5 = 0.0f;
				float x6 = 0.0f;
				float y6 = 0.0f;
				float x7 = 0.0f;
				float y7 = 0.0f;
				float x8 = 0.0f;
				float y8 = 0.0f;
				float x9 = 0.0f;
				float y9 = 0.0f;
				float x10 = 0.0f;
				float y10 = 0.0f;
				float x11 = 0.0f;
				float y11 = 0.0f;
				float x12 = 0.0f;
				float y12 = 0.0f;

				for (int i = 0; i < 200; i++)
				{
					if (i % 12 == 0)
					{
						vel = Vector3(x = x + 0.1f, y = y + 1.0f, 0.0f);
						clearEffect = new ClearEffect(position, vel, sceneTag, tag);
					}
					if (i % 12 == 1)
					{
						vel = Vector3(x2 = x2 - 0.1f, y2 = y2 + 1.0f, 0.0f);
						clearEffect = new ClearEffect(position, vel, sceneTag, tag);
					}
					if (i % 12 == 2)
					{
						vel = Vector3(x3 = x3 + 0.2f, y3 = y3 + 1.0f, 0.0f);
						clearEffect = new ClearEffect(position, vel, sceneTag, tag);
					}
					if (i % 12 == 3)
					{
						vel = Vector3(x4 = x4 - 0.2f, y4 = y4 + 1.0f, 0.0f);
						clearEffect = new ClearEffect(position, vel, sceneTag, tag);
					}
					if (i % 12 == 4)
					{
						vel = Vector3(x5 = x5 + 0.4f, y5 = y5 + 1.0f, 0.0f);
						clearEffect = new ClearEffect(position, vel, sceneTag, tag);
					}
					if (i % 12 == 5)
					{
						vel = Vector3(x6 = x6 - 0.4f, y6 = y6 + 1.0f, 0.0f);
						clearEffect = new ClearEffect(position, vel, sceneTag, tag);
					}
					if (i % 12 == 6)
					{
						vel = Vector3(x7 = x7 + 0.6f, y7 = y7 + 1.0f, 0.0f);
						clearEffect = new ClearEffect(position, vel, sceneTag, tag);
					}
					if (i % 12 == 7)
					{
						vel = Vector3(x8 = x8 - 0.6f, y8 = y8 + 1.0f, 0.0f);
						clearEffect = new ClearEffect(position, vel, sceneTag, tag);
					}
					if (i % 12 == 8)
					{
						vel = Vector3(x9 = x9 + 0.8f, y9 = y9 + 1.0f, 0.0f);
						clearEffect = new ClearEffect(position, vel, sceneTag, tag);
					}
					if (i % 12 == 9)
					{
						vel = Vector3(x10 = x10 - 0.8f, y10 = y10 + 1.0f, 0.0f);
						clearEffect = new ClearEffect(position, vel, sceneTag, tag);
					}
					if (i % 12 == 10)
					{
						vel = Vector3(x11 = x11 + 1.0f, y11 = y11 + 1.0f, 0.0f);
						clearEffect = new ClearEffect(position, vel, sceneTag, tag);
					}
					if (i % 12 == 11)
					{
						vel = Vector3(x12 = x12 - 1.0f, y12 = y12 + 1.0f, 0.0f);
						clearEffect = new ClearEffect(position, vel, sceneTag, tag);
					}

					vel.y = sinf(angle);
					angle += 10.0f;
				}

				clearEffectFlag = false;
				SetState(State::Dead);
			}
		}

		break;
	}

	prePos = owner->GetPosition();
}
