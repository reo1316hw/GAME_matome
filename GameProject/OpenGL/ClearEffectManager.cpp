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
	, mAngle(0.0f)
{
	mState = ParticleState::eParticleDisable;
	mSceneTag = _SceneTag;
	mTag = _ObjectTag;

	OneCreateClearFlag = true;

	mPlayer = _playerPtr;
	frameCount = 0;
	generateFrameCount = 0;
	generateCount = 0;
}

/*
@fn		エフェクトマネージャーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void ClearEffectManager::UpdateGameObject(float _deltaTime)
{
	if (mPlayer->GetClearFlag() && OneCreateClearFlag)
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
		break;
	case ParticleState::eParticleActive:

		mPosition = mPlayer->GetPosition();
		mPosition.z -= 200.0f;
		
		for (int i = 0; i < 50; i++)
		{
			//クリアエフェクトのカラー値
			Vector3 randVec = Vector3(rand() % 100 + 1.0f, rand() % 100 + 1.0f, rand() % 100 + 1.0f);
			randVec.Normalize();
			randVec.z *= -1.0f;

			switch (i % 4)
			{
			case 0:
				randVec.x *= -1.0f;
				randVec.y *= -1.0f;

				break;
			case 1:
				randVec.x *= 1.0f;
				randVec.y *= 1.0f;
				break;
			case 2:
				randVec.x *= -1.0f;
				randVec.y *= 1.0f;
				break;
			case 3:
				randVec.x *= 1.0f;
				randVec.y *= -1.0f;
				break;
			}

			new ParticleClearEffect(mPosition, randVec, mTag, mSceneTag);
		}

		Vector3 color = Color::sLIGHT_BLUE;
		++generateFrameCount;

		if (generateFrameCount >= 5)
		{
			float scale = 256.0f;

			//速度を決める
			//DecideVelocity(i);
			
			//向き
			Vector3 direction = Vector3(0.0f, 0.0f, -1.0f);
			//速度
			float speed = 10.0f;

			mVelocity += direction * speed;

			mRippleClearEffect = new RippleClearEffect(mPosition , mVelocity, color, scale, mTag, mSceneTag);
			++generateCount;
			generateFrameCount = 0;
		}

		if (generateCount == 3)
		{
			OneCreateClearFlag = false;
		}

		break;
	}
}

/*
@fn 速度を決める
@param _Quantity 個数
*/
void ClearEffectManager::DecideVelocity(const int _Quantity)
{
	mVelocity = Vector3::sZERO;

	//向き
	Vector3 direction = Vector3(0.0f, 0.0f, -1.0f);
	//速度
	float speed = 1.0f;

	mVelocity += direction * speed;
}