/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_pos ゴールラインの生成場所
@param	_vel ゴールラインの速度
@param	_objectTag アタッチしたゲームオブジェクトのタグ
@param	_sceneTag シーンのタグ
*/
GoalLine::GoalLine(const Vector3& _pos, const Vector3& _vel, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: ParticleEffectBase(_pos, _vel, 0, "Assets/Goal.png", _sceneTag, _objectTag)
{
	mInitPos = _pos;
	mScale = 1000.0f;
	mAlpha = 0.5f;
	mParticle->SetScale(mScale);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Vector3(1.0f, 1.0f, 1.0f));
}