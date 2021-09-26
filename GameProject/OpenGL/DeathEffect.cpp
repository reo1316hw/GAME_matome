/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos デスエフェクトの生成場所
@param	_Vel クリアエフェクトの速度
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
*/
DeathEffect::DeathEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:ParticleEffectBase(_Pos, _Vel, 40, "Assets/miniGlass.png", _SceneTag, _ObjectTag)
{
	mAlpha = 1.0f;
	mScale = 16.0f;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(Color::sWHITE);
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eParticleBlendAlpha);
	mVelocity = _Vel;
	mSpeed = 1.15f;
}

/*
@fn		デスエフェクトのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void DeathEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	//アルファ値の削減値
	const float AlphaReductionVal = 0.01f;
	//スケールの追加値
	const float ScaleAddVal = 1.0f;

	if (mLifeCount > 0)
	{
		mAlpha -= AlphaReductionVal;
		mScale += ScaleAddVal;
		mVelocity = mVelocity * mSpeed;
		mPosition = mPosition + mVelocity;

		mParticle->SetAlpha(mAlpha);
		mParticle->SetScale(mScale);
		SetPosition(mPosition);
	}

	if (mLifeCount <= 0)
	{
		mParticle->SetVisible(false);
	}
}
