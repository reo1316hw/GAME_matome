/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
@param _playerPtr プレイヤーのポインタ
*/
DeathEffectManager::DeathEffectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
	:GameObject(_SceneTag, _ObjectTag)
	, mRandVel(Vector3::sZERO)
{
	mState = ParticleState::eParticleDisable;
	mSceneTag = _SceneTag;
	mTag = _ObjectTag;

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
		mState = ParticleState::eParticleActive;
	}
	else
	{
		mState = ParticleState::eParticleDisable;
	}

	switch (mState)
	{
	case ParticleState::eParticleDisable:

		mCreateDeathEffectCount = 0;

		break;
	case ParticleState::eParticleActive:

		//デスエフェクトの個数
		const int DeathEffectNum = 50;

		mPosition = mPlayer->GetPosition();

		for (int i = 0; i < DeathEffectNum; i++)
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
@param _Quantity 個数
*/
void DeathEffectManager::DecideVelocity(const int _Quantity)
{
	//方向の個数
	const int DirectionNum = 3;
	//向き
	const float Direction = 1.0f;

	mRandVel = Vector3(rand() % 100 + 1.0f, rand() % 100 + 1.0f, rand() % 100 + 1.0f);
	mRandVel.Normalize();

	switch (_Quantity % DirectionNum)
	{
	case eLeftDeath:
		mRandVel.x *= -Direction;
		break;
	case eBackDeath:
		mRandVel.z *= -Direction;
		break;
	case eLeftBackDeath:
		mRandVel.x *= -Direction;
		mRandVel.z *= -Direction;
		break;
	}
}
