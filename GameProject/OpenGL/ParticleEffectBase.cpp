/*
@file ParticleEffectBase.h
@brief 一定時間で消える、主にエフェクトの基底クラスとして使用されるクラス
*/

/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos エフェクトの生成場所
@param	_Vel エフェクトの速度
@param	_LifeCount エフェクトの生存時間
@param	_ParticleFileName 画像へのアドレス
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
@param	_Scale 画像の拡大サイズ
*/
ParticleEffectBase::ParticleEffectBase(const Vector3& _Pos, const Vector3& _Vel, const int& _LifeCount, const std::string& _ParticleFileName, const SceneBase::Scene _SceneTag, const Tag& _ObjectTag,const float& _Scale)
	: GameObject(_SceneTag,_ObjectTag)
	 ,mLifeCount(_LifeCount)
{
	mVelocity = _Vel;
	mParticle = new ParticleComponent(this);
	mParticle->SetTextureID(RENDERER->GetTexture(_ParticleFileName)->GetTextureID());
	mParticle->SetColor(Color::sWHITE);
	mParticle->SetScale(_Scale);
	SetPosition(_Pos);
}

/*
@fn		派生クラスの更新関数を呼び座標に移動量を足し続ける
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void ParticleEffectBase::UpdateGameObject(float _deltaTime)
{
	LifeCountDown();
	SetPosition(mPosition + mVelocity);
}

/*
@fn 生存時間をカウントダウンする関数。派生クラスで更新関数を決定した場合そこに追加すること。
*/
void ParticleEffectBase::LifeCountDown()
{
	//生存時間がゼロになるとこのオブジェクトを更新終了する
	if (mLifeCount <= 0)
	{
		mParticle->SetVisible(false);
		SetState(State::Dead);
	}
	else
	{
		mParticle->SetVisible(true);
		mLifeCount--;
	}

}

/*
@param _flag 反転を行うか
*/
void ParticleEffectBase::SetReverve(float _flag)
{
	mParticle->SetReverce(_flag);
}