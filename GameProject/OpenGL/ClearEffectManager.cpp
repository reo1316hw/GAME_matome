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

		//クリアエフェクトの個数
		const int ClearEffectNum = 360;
		mPosition = mPlayer->GetPosition();
		mPosition.z -= 200.0f;

		//カラーの減速値
		const Vector3 decColor = Vector3(0.002f, 0.002f, 0.0f);
		//クリアエフェクトのカラー値
		Vector3 color = Color::sWHITE;

		for (int i = 0; i < ClearEffectNum; i++)
		{
			//速度を決める
			DecideVelocity();

			color -= decColor;

			mClearEffect = new ClearEffect(mPosition, mVelocity, color, mTag, mSceneTag);
		}

		OneCreateClearFlag = false;

		break;
	}
}

/*
@fn    速度を決める
*/
void ClearEffectManager::DecideVelocity()
{
	//向き
	Vector3 direction = Vector3(cosf(mAngle), sinf(mAngle), -0.3f);
	//速度
	Vector3 speed = Vector3(2.0f, 2.0f, 1.1f);

	mVelocity += direction * speed;
	mAngle += 0.1f;
}