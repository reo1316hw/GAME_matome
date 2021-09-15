/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_pos クリアエフェクトの生成場所
@param	_vel クリアエフェクトの速度
@param	_objectTag アタッチしたゲームオブジェクトのタグ
@param	_sceneTag シーンのタグ
*/
CheckpointEffect::CheckpointEffect(Vector3 _pos, Vector3 _vel, const Tag& _objectTag, SceneBase::Scene _sceneTag)
	:ParticleEffectBase(_pos, _vel, 60, "Assets/star.png", _sceneTag, _objectTag)
{
	mAlpha = ALPHA_INITIAL_VALUE;
	mScale = SCALE_INITIAL_VALUE;
	mVelocity.y = VELOCITY_INITIAL_VALUE;
	mSpeed = ACCELERATION_INITIAL_VALUE;
	mParticle->SetAlpha(mAlpha);
	mParticle->SetScale(mScale);
	mParticle->SetColor(Color::Yellow);
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
		mVelocity = mVelocity * mSpeed;
		mPosition = mPosition + mVelocity;

		mVelocity.y -= VELOCITY_MINUS_VALUE;
		
		if (mScale <= SCALE_MAX_VALUE)
		{
			mScale += SCALE_PLUS_VALUE;
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