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
ClearEffectManager::ClearEffectManager(const Tag& _objectTag, SceneBase::Scene _sceneTag, Player* _playerPtr)
	:GameObject(_sceneTag, _objectTag)
{
	mState = ParticleState::PARTICLE_DISABLE;
	mSceneTag = _sceneTag;
	mTag = _objectTag;

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

		mPosition = mPlayer->GetPosition();
		mPosition.y -= 10.0f;
		mPosition.z -= 20.0f;

		float x = 0.0f;
		float y = 0.0f;
		float x2 = 0.0f;
		float y2 = 0.0f;
		float x3 = 0.0f;
		float y3 = 0.0f;
		float x4 = 0.0f;
		float y4 = 0.0f;
		float x5 = 0.0f;
		float y5 = 0.0f;
		float x6 = 0.0f;
		float y6 = 0.0f;
		float x7 = 0.0f;
		float y7 = 0.0f;
		float x8 = 0.0f;
		float y8 = 0.0f;
		float x9 = 0.0f;
		float y9 = 0.0f;
		float x10 = 0.0f;
		float y10 = 0.0f;
		float x11 = 0.0f;
		float y11 = 0.0f;
		float x12 = 0.0f;
		float y12 = 0.0f;

		//角度
		float	mAngle = 0.0f;

		Vector3 vel = Vector3(0.0f, 0.0f, 0.0f);

		//クリアエフェクトを生成
		mClearEffect = new ClearEffect(mPosition, vel, mTag, mSceneTag);

		for (int i = 0; i < 200; i++)
		{
			if (i % 12 == 0)
			{
				vel = Vector3(x = x + 0.1f, y = y + 1.0f, 0.0f);
				mClearEffect = new ClearEffect(mPosition, vel, mTag, mSceneTag);
			}
			if (i % 12 == 1)
			{
				vel = Vector3(x2 = x2 - 0.1f, y2 = y2 + 1.0f, 0.0f);
				mClearEffect = new ClearEffect(mPosition, vel, mTag, mSceneTag);
			}
			if (i % 12 == 2)
			{
				vel = Vector3(x3 = x3 + 0.2f, y3 = y3 + 1.0f, 0.0f);
				mClearEffect = new ClearEffect(mPosition, vel, mTag, mSceneTag);
			}
			if (i % 12 == 3)
			{
				vel = Vector3(x4 = x4 - 0.2f, y4 = y4 + 1.0f, 0.0f);
				mClearEffect = new ClearEffect(mPosition, vel, mTag, mSceneTag);
			}
			if (i % 12 == 4)
			{
				vel = Vector3(x5 = x5 + 0.4f, y5 = y5 + 1.0f, 0.0f);
				mClearEffect = new ClearEffect(mPosition, vel, mTag, mSceneTag);
			}
			if (i % 12 == 5)
			{
				vel = Vector3(x6 = x6 - 0.4f, y6 = y6 + 1.0f, 0.0f);
				mClearEffect = new ClearEffect(mPosition, vel, mTag, mSceneTag);
			}
			if (i % 12 == 6)
			{
				vel = Vector3(x7 = x7 + 0.6f, y7 = y7 + 1.0f, 0.0f);
				mClearEffect = new ClearEffect(mPosition, vel, mTag, mSceneTag);
			}
			if (i % 12 == 7)
			{
				vel = Vector3(x8 = x8 - 0.6f, y8 = y8 + 1.0f, 0.0f);
				mClearEffect = new ClearEffect(mPosition, vel, mTag, mSceneTag);
			}
			if (i % 12 == 8)
			{
				vel = Vector3(x9 = x9 + 0.8f, y9 = y9 + 1.0f, 0.0f);
				mClearEffect = new ClearEffect(mPosition, vel, mTag, mSceneTag);
			}
			if (i % 12 == 9)
			{
				vel = Vector3(x10 = x10 - 0.8f, y10 = y10 + 1.0f, 0.0f);
				mClearEffect = new ClearEffect(mPosition, vel, mTag, mSceneTag);
			}
			if (i % 12 == 10)
			{
				vel = Vector3(x11 = x11 + 1.0f, y11 = y11 + 1.0f, 0.0f);
				mClearEffect = new ClearEffect(mPosition, vel, mTag, mSceneTag);
			}
			if (i % 12 == 11)
			{
				vel = Vector3(x12 = x12 - 1.0f, y12 = y12 + 1.0f, 0.0f);
				mClearEffect = new ClearEffect(mPosition, vel, mTag, mSceneTag);
			}

			vel.y = sinf(mAngle);
			mAngle += 10.0f;
		}

		OneCreateClearFlag = false;

		break;
	}
}