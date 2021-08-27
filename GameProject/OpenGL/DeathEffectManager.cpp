/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_owner ゲームオブジェクトクラスのポインタ
@param	_objectTag アタッチしたゲームオブジェクトのタグ
@param	_sceneTag シーンのタグ
*/
DeathEffectManager::DeathEffectManager(GameObject* _owner, const Tag& _objectTag, SceneBase::Scene _sceneTag)
	:GameObject(_sceneTag, _objectTag)
{
	mOwner = _owner;
	mState = ParticleState::PARTICLE_DISABLE;
	mSceneTag = _sceneTag;
	mTag = _objectTag;

	mAngle = 0.0f;

	OneCreateDeathFlag = true;
}

/*
@fn		エフェクトマネージャーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void DeathEffectManager::UpdateGameObject(float _deltaTime)
{
	if (mPlayer->GetDeathFlag() && OneCreateDeathFlag == true)
	{
		mState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		mState = ParticleState::PARTICLE_DISABLE;
	}

	Vector3 vel = Vector3(0.0f, 0.0f, 0.0f);

	switch (mState)
	{
	case PARTICLE_DISABLE:

		mCreateDeathEffectCount = 0;

		break;
	case PARTICLE_ACTIVE:

		mPosition = mOwner->GetPosition();
		mPosition.y -= 10.0f;
		mPosition.z -= 20.0f;

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

			mDeathEffect = new DeathEffect(mPosition, randVel, mTag, mSceneTag);
		}

		OneCreateDeathFlag = false;

		break;
	}
}
