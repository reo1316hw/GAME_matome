/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_owner ゲームオブジェクトクラスのポインタ
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
*/
SandEffectManager::SandEffectManager(GameObject* _owner, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:GameObject(_SceneTag, _ObjectTag)
{
	mOwner = _owner;
	mState = ParticleState::eParticleDisable;
	mPos = Vector3::sZERO;
	mSceneTag = _SceneTag;
	mTag = _ObjectTag;
}

/*
@fn		エフェクトマネージャーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void SandEffectManager::UpdateGameObject(float _deltaTime)
{
	if (mPos != mOwner->GetPosition())
	{
		mState = ParticleState::eParticleActive;
	}
	else
	{
		mState = ParticleState::eParticleDisable;
	}

	Vector3 vel = Vector3::sZERO;

	switch (mState)
	{
	case ParticleState::eParticleDisable:
		break;
	case ParticleState::eParticleActive:

		//ポジションをずらすための定数
		const Vector3 ShittPos = Vector3(0.0f, 10.0f, 20.0f);
		//生成するタイミング
		const int CreateTiming = 6;

		mCreateSandEffectCount++;
		mPosition = mOwner->GetPosition();
		mPosition -= ShittPos;

		//6フレームごとに生成する
		if (mCreateSandEffectCount % CreateTiming == 0)
		{
			vel = Vector3(0.0f, 0.0f, -1.0);
			mSandEffect = new SandEffect(mPosition, vel, mSceneTag, mTag);
		}		

		break;
	}

	mPos = mOwner->GetPosition();
}
