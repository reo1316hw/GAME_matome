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
ClearEffectManager::ClearEffectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
	:GameObject(_SceneTag, _ObjectTag)
{
	mState = ParticleState::PARTICLE_DISABLE;
	mSceneTag = _SceneTag;
	mTag = _ObjectTag;

	OneCreateClearFlag = true;

	mPlayer = _playerPtr;
}

/*
@fn		エフェクトマネージャーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void ClearEffectManager::UpdateGameObject(float _deltaTime)
{
	if (mPlayer->GetClearFlag() && OneCreateClearFlag)
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
		break;
	case PARTICLE_ACTIVE:

		//クリアエフェクトの個数
		const int ClearEffectNum = 200;
		mPosition = mPlayer->GetPosition();

		for (int i = 0; i < ClearEffectNum; i++)
		{
			DecideVelocity(i);

			mClearEffect = new ClearEffect(mPosition, mVelocity, mTag, mSceneTag);
		}

		OneCreateClearFlag = false;

		break;
	}
}

/*
@fn    速度を決める
@param _Quantity 個数
*/
void ClearEffectManager::DecideVelocity(const int _Quantity)
{
	//方向の個数
	const int DirectionNum = 5;
	//向き
	float direction = 0.0f;
	//速度
	float speed = 0.0f;

	//速度を初期化
	mVelocity = Vector3::sZERO;
	speed = _Quantity * 0.1f;

	switch (_Quantity % DirectionNum)
	{
	case eLeftUpClear:
		direction = -0.6f;
		mVelocity.x = direction * speed;
		direction = 1.0f;
		mVelocity.y = direction * speed;
		break;
	case eLeftUpUpClear:
		direction = -0.3f;
		mVelocity.x = direction * speed;
		direction = 1.0f;
		mVelocity.y = direction * speed;
		break;
	case eUpClear:
		direction = 1.0f;
		mVelocity.y = direction * speed;
		break;
	case eRightUpUpClear:
		direction = 0.3f;
		mVelocity.x = direction * speed;
		direction = 1.0f;
		mVelocity.y = direction * speed;
		break;
	case eRightUpClear:
		direction = 0.6f;
		mVelocity.x = direction * speed;
		direction = 1.0f;
		mVelocity.y = direction * speed;
		break;
	}
}