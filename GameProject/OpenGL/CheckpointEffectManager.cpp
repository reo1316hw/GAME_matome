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
CheckpointEffectManager::CheckpointEffectManager(const Tag& _objectTag, SceneBase::Scene _sceneTag, Player* _playerPtr)
	:GameObject(_sceneTag, _objectTag)
{
	mState = ParticleState::PARTICLE_DISABLE;
	mSceneTag = _sceneTag;
	mTag = _objectTag;

	a = true;

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
			//速度を初期化
			Vector3 vel = Vector3::Zero;

			//各方向の速度と向きを計算
			switch (i % 8)
			{
			case 0:
				vel.x = DIRECTION * SPEED;
				break;
			case 1:
				vel.z = DIRECTION * SPEED;
				break;
			case 2:
				vel.x = -DIRECTION * SPEED;
				break;
			case 3:
				vel.z = -DIRECTION * SPEED;
				break;
			case 4:
				vel.x = DIRECTION * SPEED;
				vel.z = DIRECTION * SPEED;
				break;
			case 5:
				vel.x = -DIRECTION * SPEED;
				vel.z = -DIRECTION * SPEED;
				break;
			case 6:
				vel.x = DIRECTION * SPEED;
				vel.z = -DIRECTION * SPEED;
				break;
			case 7:
				vel.x = -DIRECTION * SPEED;
				vel.z = DIRECTION * SPEED;
				break;
			}

			//チェックポイントエフェクトを生成
			mCheckpointEffect = new CheckpointEffect(mPosition, vel, mTag, mSceneTag);
		}

		mState = ParticleState::PARTICLE_DISABLE;
		break;
	}
}
