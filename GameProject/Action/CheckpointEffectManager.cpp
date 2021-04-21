/*
@brief	インクルード
*/
#include "CheckpointEffectManager.h"
#include "CheckpointEffect.h"
#include "Player.h"

/*
@fn		コンストラクタ
@param	_owner ゲームオブジェクトクラスのポインタ
@param	_objectTag アタッチしたゲームオブジェクトのタグ
@param	_sceneTag シーンのタグ
*/
CheckpointEffectManager::CheckpointEffectManager(GameObject* _owner, const Tag& _objectTag, SceneBase::Scene _sceneTag)
	:GameObject(_sceneTag, _objectTag)
{
	mOwner = _owner;
	mState = ParticleState::PARTICLE_DISABLE;
	mSceneTag = _sceneTag;
	mTag = _objectTag;

	mCheckpointFlag = false;
}

/*
@fn		エフェクトマネージャーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void CheckpointEffectManager::UpdateGameObject(float _deltaTime)
{
	if (mPlayer->GetCheckpointFlag())
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

		mPosition = mOwner->GetPosition();

		for (int i = 0; i < 8; i++)
		{
			Vector3 vel = Vector3::Zero;

			switch (i % 8)
			{
			case 0:
				vel.x = DIRECTION * SPEED;
				break;
			case 1:
				vel.y = DIRECTION * SPEED;
				break;
			case 2:
				vel.x = -DIRECTION * SPEED;
				break;
			case 3:
				vel.y = -DIRECTION * SPEED;
				break;
			case 4:
				vel.x = DIRECTION * SPEED;
				vel.y = DIRECTION * SPEED;
				break;
			case 5:
				vel.x = -DIRECTION * SPEED;
				vel.y = -DIRECTION * SPEED;
				break;
			case 6:
				vel.x = DIRECTION * SPEED;
				vel.y = -1.0f * SPEED;
				break;
			case 7:
				vel.x = -DIRECTION * SPEED;
				vel.y = DIRECTION * SPEED;
				break;
			}

			mCheckpointEffect = new CheckpointEffect(mPosition, vel, mTag, mSceneTag);
		}

		break;
	}
}
