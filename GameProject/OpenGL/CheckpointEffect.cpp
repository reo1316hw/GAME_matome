/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos クリアエフェクトの生成場所
@param	_Vel クリアエフェクトの速度
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
*/
CheckpointEffect::CheckpointEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:ParticleEffectBase(_Pos, _Vel, 60, "Assets/star.png", _SceneTag, _ObjectTag)
{
	mAlpha = 1.0f;
	mScale = 0.0f;
	mVelocity.y = 30.0f;
	mSpeed = 1.0f;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(Color::sYELLOW);
	mParticle->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM_ALPHA);
}

/*
@fn		クリアエフェクトのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void CheckpointEffect::UpdateGameObject(float _deltaTime)
{
	//生存時間をカウント
	ParticleEffectBase::LifeCountDown();

	//ライフカウントが0より大きかったら速度、透明度、スケールの値を更新
	if (mLifeCount > 0)
	{
		//速度の減速値
		const float VelocityMinusValue = 1.5f;
		//スケールの加速値
		const float ScalePlusValue = 4.0f;
		//スケールの最大値
		const float ScaleMaxValue = 64.0f;

		mVelocity = mVelocity * mSpeed;
		mPosition = mPosition + mVelocity;

		mVelocity.y -= VelocityMinusValue;
		
		if (mScale <= ScaleMaxValue)
		{
			mScale += ScalePlusValue;
		}

		mParticle->SetScale(mScale);
		SetPosition(mPosition);
	}

	//ライフカウントが0以下だったら見えなくする
	if (mLifeCount <= 0)
	{
		mParticle->SetVisible(false);
	}
}