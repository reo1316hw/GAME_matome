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
	, mCreateTimingCount(0)
	, mCreateCount(0)
{
	mState = ParticleState::eParticleDisable;
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

		//粒子のクリアエフェクト生成
		CreateParticleClearEffect();
		
		//波紋のクリアエフェクト生成
		CreateRippleClearEffect();

		break;
	}
}

/*
@fn 粒子のクリアエフェクト生成
*/
void ClearEffectManager::CreateParticleClearEffect()
{
	//速度
	const float Speed = 30.0f;
	//1フレームに発生する粒子のクリアエフェクトの個数
	const int ParticleClearEffectNum = 4;

	mPosition = mPlayer->GetPosition();
	mPosition.z -= 200.0f;

	for (int i = 0; i < ParticleClearEffectNum; i++)
	{
		//粒子のクリアエフェクトのランダムな向きベクトル
		Vector3 randVec = Vector3(rand() % 100 + 1.0f, rand() % 100 + 1.0f, rand() % 100 + 1.0f);

		randVec.Normalize();
		randVec.z *= -Speed;

		//方向の個数
		const int DirectionNum = 4;

		//後方だけに粒子のクリアエフェクトを飛ばすように向きを限定する
		switch (i % DirectionNum)
		{
		case DirectionClearEffect::eLeftUnderClear:
			randVec.x *= -Speed;
			randVec.y *= -Speed;

			break;
		case DirectionClearEffect::eRightUpClear:
			randVec.x *= Speed;
			randVec.y *= Speed;
			break;
		case DirectionClearEffect::eLeftUpClear:
			randVec.x *= -Speed;
			randVec.y *= Speed;
			break;
		case DirectionClearEffect::eRightUnderClear:
			randVec.x *= Speed;
			randVec.y *= -Speed;
			break;
		}

		new ParticleClearEffect(mPosition, randVec, mTag, mSceneTag);
	}
}

/*
@fn 波紋のクリアエフェクト生成
*/
void ClearEffectManager::CreateRippleClearEffect()
{
	//生成するタイミング
	const int CreateTimingNum = 5;
	//生成する最大個数
	const int MaxCreateNum = 3;

	++mCreateTimingCount;

	if (mCreateTimingCount >= CreateTimingNum)
	{
		//速度を決める
		DecideVelocity();

		mRippleClearEffect = new RippleClearEffect(mPosition, mVelocity, mTag, mSceneTag);

		++mCreateCount;
		mCreateTimingCount = 0;
	}

	if (mCreateCount == MaxCreateNum)
	{
		OneCreateClearFlag = false;
	}
}

/*
@fn 速度を決める
*/
void ClearEffectManager::DecideVelocity()
{
	mVelocity = Vector3::sZERO;

	//向き
	Vector3 direction = Vector3(0.0f, 0.0f, -1.0f);
	//速度
	float speed = 10.0f;

	mVelocity += direction * speed;
}