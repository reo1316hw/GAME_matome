/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos ゴールラインの生成場所
@param	_Vel ゴールラインの速度
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
*/
GoalLine::GoalLine(const Vector3& _Pos, const Vector3& _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: ParticleEffectBase(_Pos, _Vel, 0, "Assets/Goal.png", _SceneTag, _ObjectTag)
{
	mInitPos = _Pos;
	mScale = 1000.0f;
	mAlpha = 0.5f;
	mParticle->SetScale(mScale);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Color::sWHITE);
}