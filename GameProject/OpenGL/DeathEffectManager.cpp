/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_objectTag アタッチしたゲームオブジェクトのタグ
@param	_sceneTag シーンのタグ
@param _playerPtr プレイヤーのポインタ
*/
DeathEffectManager::DeathEffectManager(const Tag& _objectTag, SceneBase::Scene _sceneTag, Player* _playerPtr)
	:GameObject(_sceneTag, _objectTag)
{
	mState = ParticleState::PARTICLE_DISABLE;
	mSceneTag = _sceneTag;
	mTag = _objectTag;

	mAngle = 0.0f;

	OneCreateDeathFlag = true;

	mPlayer = _playerPtr;
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

		mPosition = mPlayer->GetPosition();
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
