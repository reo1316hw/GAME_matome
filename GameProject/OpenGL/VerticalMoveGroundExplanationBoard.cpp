/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos 縦移動床の説明パネルの座標
@param	_Vel 縦移動床の説明パネルの速度
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
*/
VerticalMoveGroundExplanationBoard::VerticalMoveGroundExplanationBoard(const Vector3& _Pos, const Vector3& _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: ParticleEffectBase(_Pos, _Vel, 0, "Assets/Texture/Board/TutorialVerticlMoveGround.png", _SceneTag, _ObjectTag)
{
	mInitPos = _Pos;
	mScale = 400.0f;
	mAlpha = 1.0f;
	mParticle->SetScale(mScale);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Color::sWHITE);
}