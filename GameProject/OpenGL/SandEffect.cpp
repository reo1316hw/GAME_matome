/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos 砂ぼこりの座標
@param	_Vel 砂ぼこりの速度
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
*/
SandEffect::SandEffect(const Vector3 _Pos, const Vector3 _Vel, const SceneBase::Scene _SceneTag,const Tag& _ObjectTag)
	:ParticleEffectBase(_Pos,_Vel,30,"Assets/PhotonB.png", _SceneTag, _ObjectTag)
{
	const Vector3 Color = Vector3(0.95f, 0.95f, 0.95f);
	mAlpha = 0.5f;
	mScale = 32.0f;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(Color);
	mParticle->SetBlendMode(ParticleComponent::ParticleEnum::eParticleBlendAlpha);
}

/*
@fn		砂ぼこりのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void SandEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	//アルファ値の削減値
	const float AlphaReductionVal = 0.01f;
	//スケールの追加値
	const float ScaleAddVal = 10.0f;

	if (mLifeCount > 0)
	{
		mAlpha -= AlphaReductionVal;
		mScale += ScaleAddVal;
		mPosition = mPosition + mVelocity;

		mParticle->SetAlpha(mAlpha);
		mParticle->SetScale(mScale);
		SetPosition(mPosition);
	}

	if (mLifeCount <=0)
	{
		mParticle->SetVisible(false);
	}
}
