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
CheckpointEffectManager::CheckpointEffectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
	:GameObject(_SceneTag, _ObjectTag)
{
	mState = ParticleState::eParticleDisable;
	mSceneTag = _SceneTag;
	mTag = _ObjectTag;

	mPlayer = _playerPtr;
}

/*
@fn		エフェクトマネージャーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void CheckpointEffectManager::UpdateGameObject(float _deltaTime)
{
	//チェックポイントを通過したらチェックポイントエフェクトをアクティブにする
	if (mPlayer->GetEnableCheckpointFlag())
	{
		mState = ParticleState::eParticleActive;
	}
	else
	{
		mState = ParticleState::eParticleDisable;
	}

	//チェックポイントのステートを調べてチェックポイントエフェクトの処理を行う
	switch (mState)
	{
	//アクティブじゃないなら
	case ParticleState::eParticleDisable:
		break;
	//アクティブなら
	case ParticleState::eParticleActive:
		
		//親のポジションを取得
		mPosition = mPlayer->GetPosition();

		//8方向にチェックポイントエフェクトを飛ばす
		for (int i = 0; i < 8; i++)
		{
			// チェックポイントエフェクトの向きを決める
			DecideVelocity(i);
			//チェックポイントエフェクトを生成
			mCheckpointEffect = new CheckpointEffect(mPosition, mVelocity, mTag, mSceneTag);
		}

		mState = ParticleState::eParticleDisable;
		break;
	}
}

/*
@fn    速度を決める
@param _Quantity 個数
*/
void CheckpointEffectManager::DecideVelocity(const int _Quantity)
{
	//方向の個数
	const int DirectionNum = 8;
	//速度
	const float Speed = 10.0f;
	//向き
	const float Direction = 1.0f;

	//速度を初期化
	mVelocity = Vector3::sZERO;

	//各方向の速度と向きを計算
	switch (_Quantity % DirectionNum)
	{
	case DirectionCheckpointEffect::eRightCheckpoint:
		mVelocity.x = Direction * Speed;
		break;
	case DirectionCheckpointEffect::eFrontCheckpoint:
		mVelocity.z = Direction * Speed;
		break;
	case DirectionCheckpointEffect::eLeftCheckpoint:
		mVelocity.x = -Direction * Speed;
		break;
	case DirectionCheckpointEffect::eBackCheckpoint:
		mVelocity.z = -Direction * Speed;
		break;
	case DirectionCheckpointEffect::eRightFrontCheckpoint:
		mVelocity.x = Direction * Speed;
		mVelocity.z = Direction * Speed;
		break;
	case DirectionCheckpointEffect::eLeftBackCheckpoint:
		mVelocity.x = -Direction * Speed;
		mVelocity.z = -Direction * Speed;
		break;
	case DirectionCheckpointEffect::eRightBackCheckpoint:
		mVelocity.x = Direction * Speed;
		mVelocity.z = -Direction * Speed;
		break;
	case DirectionCheckpointEffect::eLeftFrontCheckpoint:
		mVelocity.x = -Direction * Speed;
		mVelocity.z = Direction * Speed;
		break;
	}
}