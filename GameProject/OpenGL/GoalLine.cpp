/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos ゴールラインの座標
@param	_Vel ゴールラインの速度
@param	_TextureName テクスチャデータのパス
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
@param	_playerPtr プレイヤーのポインタ
*/
GoalLine::GoalLine(const Vector3& _Pos, const Vector3& _Vel, const std::string& _TextureName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
	: ParticleEffectBase(_Pos, _Vel, 0, _TextureName, _SceneTag, _ObjectTag)
{
	mInitPos = _Pos;
	mPosition = _Pos;
	mVelocity = _Vel;
	mScale = 100.0f;
	mAlpha = 0.5f;
	mParticle->SetScale(mScale);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Color::sWHITE);

	mPlayer = _playerPtr;
}

void GoalLine::UpdateGameObject(float _deltaTime)
{
	if (mPlayer->GetGoalProductionFlag())
	{
		mVelocity *= 1.05f;
		mPosition += mVelocity;
	}
	
	SetPosition(mPosition);
}
