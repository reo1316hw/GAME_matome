/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos ゴールワープ板の座標
@param	_Vel ゴールワープ板の速度
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
*/
GoalWarpBorard::GoalWarpBorard(const Vector3& _Pos, const Vector3& _Vel, const std::string& _ParticleFileName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: ParticleEffectBase(_Pos, _Vel, 0, _ParticleFileName, _SceneTag, _ObjectTag)
	, mAngle(0.0f)
{
	mInitPos = _Pos;
	mScale = 1000.0f;
	mAlpha = 0.5f;
	mParticle->SetScale(mScale);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Color::sWHITE);
}

/*
@fn		ゴールワープ板のアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void GoalWarpBorard::UpdateGameObject(float _deltaTime)
{
	mAngle += 10.0f;
	//回転処理
	float radian = Math::ToRadians(mAngle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::sUNIT_Z, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}