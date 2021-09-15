/*
@brief インクルード
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
	, mRandVel(Vector3::Zero)
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
			DecideVelocity(i);

			mDeathEffect = new DeathEffect(mPosition, mRandVel, mTag, mSceneTag);
		}

		OneCreateDeathFlag = false;

		break;
	}
}

/*
@fn    速度を決める
@param _quantity 個数
*/
void DeathEffectManager::DecideVelocity(const int _quantity)
{
	mRandVel = Vector3(rand() % 100 + 1.0f, rand() % 100 + 1.0f, rand() % 100 + 1.0f);
	mRandVel.Normalize();

	if (_quantity % 2 == 0)
	{
		mRandVel.x *= -1.0f;
		mRandVel.z *= -1.0f;
	}

	if (_quantity % 5 == 0)
	{
		mRandVel.x *= -1.0f;
	}

	if (_quantity % 3 == 0)
	{
		mRandVel.z *= -1.0f;
	}
}
