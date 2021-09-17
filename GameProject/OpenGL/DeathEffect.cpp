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
	mParticle->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM_ALPHA);
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

	if (mLifeCount > 0)
	{
		mAlpha -= 0.01f;
		mScale += 1.0f;
		mParticle->SetAlpha(mAlpha);
		mParticle->SetScale(mScale);

		mVelocity = mVelocity * mSpeed;
		mPosition = mPosition + mVelocity;
		SetPosition(mPosition);
	}

	if (mLifeCount <= 0)
	{
		mParticle->SetVisible(false);
	}
}
