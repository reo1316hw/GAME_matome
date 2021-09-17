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
	mState = ParticleState::PARTICLE_DISABLE;
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
		mState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		mState = ParticleState::PARTICLE_DISABLE;
	}

	//チェックポイントのステートを調べてチェックポイントエフェクトの処理を行う
	switch (mState)
	{
	//アクティブじゃないなら
	case PARTICLE_DISABLE:
		break;
	//アクティブなら
	case PARTICLE_ACTIVE:
		
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

		mState = ParticleState::PARTICLE_DISABLE;
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
	case eRightCheckpoint:
		mVelocity.x = Direction * Speed;
		break;
	case eFrontCheckpoint:
		mVelocity.z = Direction * Speed;
		break;
	case eLeftCheckpoint:
		mVelocity.x = -Direction * Speed;
		break;
	case eBackCheckpoint:
		mVelocity.z = -Direction * Speed;
		break;
	case eRightFrontCheckpoint:
		mVelocity.x = Direction * Speed;
		mVelocity.z = Direction * Speed;
		break;
	case eLeftBackCheckpoint:
		mVelocity.x = -Direction * Speed;
		mVelocity.z = -Direction * Speed;
		break;
	case eRightBackCheckpoint:
		mVelocity.x = Direction * Speed;
		mVelocity.z = -Direction * Speed;
		break;
	case eLeftFrontCheckpoint:
		mVelocity.x = -Direction * Speed;
		mVelocity.z = Direction * Speed;
		break;
	}
}