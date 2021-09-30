/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos 粒子のクリアエフェクトの生成場所
@param	_Vel 粒子のクリアエフェクトの速度
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
*/
ParticleClearEffect::ParticleClearEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:ParticleEffectBase(_Pos, _Vel, 60, "Assets/Texture/Effect/Particle.png", _SceneTag, _ObjectTag)
{
	mAlpha = 1.0f;
	mScale = 0.0f;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(Color::sWHITE);
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eParticleBlendAdd);
}

/*
@fn		クリアエフェクトのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void ParticleClearEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	//元の位置に戻していくタイミング
	const int TimingBackPos = 30;
	//スケールの変動値
	const float FluctuationScaleVal = 8.0f;

	if (mLifeCount <= TimingBackPos)
	{
		mScale -= FluctuationScaleVal;
		mPosition += mVelocity * -1.0f;
	}
	else
	{
		mScale += FluctuationScaleVal;
		mPosition += mVelocity;
	}

	mParticle->SetScale(mScale);
	SetPosition(mPosition);

	if (mLifeCount <= 0)
	{
		mParticle->SetVisible(false);
	}
}
