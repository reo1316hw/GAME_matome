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
CheckpointEffectManager::CheckpointEffectManager(const Tag& _objectTag, SceneBase::Scene _sceneTag, Player* _playerPtr)
	:GameObject(_sceneTag, _objectTag)
{
	mState = ParticleState::PARTICLE_DISABLE;
	mSceneTag = _sceneTag;
	mTag = _objectTag;

	mPlayer = _playerPtr;
}

/*
@fn		エフェクトマネージャーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void CheckpointEffectManager::UpdateGameObject(float _deltaTime)
{
	//チェックポイントを通過したらチェックポイントエフェクトをアクティブにする
	if (mPlayer->GetCheckpointFlag())
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
@param _quantity 個数
*/
void CheckpointEffectManager::DecideVelocity(const int _quantity)
{
	//速度を初期化
	mVelocity = Vector3::Zero;

	//各方向の速度と向きを計算
	switch (_quantity % 8)
	{
	case 0:
		mVelocity.x = DIRECTION * SPEED;
		break;
	case 1:
		mVelocity.z = DIRECTION * SPEED;
		break;
	case 2:
		mVelocity.x = -DIRECTION * SPEED;
		break;
	case 3:
		mVelocity.z = -DIRECTION * SPEED;
		break;
	case 4:
		mVelocity.x = DIRECTION * SPEED;
		mVelocity.z = DIRECTION * SPEED;
		break;
	case 5:
		mVelocity.x = -DIRECTION * SPEED;
		mVelocity.z = -DIRECTION * SPEED;
		break;
	case 6:
		mVelocity.x = DIRECTION * SPEED;
		mVelocity.z = -DIRECTION * SPEED;
		break;
	case 7:
		mVelocity.x = -DIRECTION * SPEED;
		mVelocity.z = DIRECTION * SPEED;
		break;
	}
}