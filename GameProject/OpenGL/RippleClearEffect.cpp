/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos 波紋のクリアエフェクトの生成場所
@param	_Vel 波紋のクリアエフェクトの速度
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
*/
RippleClearEffect::RippleClearEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:ParticleEffectBase(_Pos, _Vel, 50, "Assets/Texture/Effect/Ripple.png", _SceneTag, _ObjectTag)
{
	mAlpha = 1.0f;
	mScale = 0.0f;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(Color::sNAVY);
	mParticle->SetBlendMode(ParticleComponent::ParticleBlendType::eParticleBlendAlpha);
}

/*
@fn		クリアエフェクトのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void RippleClearEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	//元の位置に戻していくタイミング
	const int TimingBackPos = 25;
	//スケールの変動値
	const float FluctuationScaleVal = 64.0f;

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
