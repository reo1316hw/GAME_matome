/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_pos 縦移動床の説明パネルの座標
@param	_vel 縦移動床の説明パネルの速度
@param	_objectTag アタッチしたゲームオブジェクトのタグ
@param	_sceneTag シーンのタグ
*/
VerticalMoveGroundExplanationBoard::VerticalMoveGroundExplanationBoard(const Vector3& _pos, const Vector3& _velocity, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: ParticleEffectBase(_pos, _velocity, 0, "Assets/tutorial01.png", _sceneTag, _objectTag)
{
	mInitPos = _pos;
	mScale = 400.0f;
	mAlpha = 1.0f;
	mParticle->SetScale(mScale);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Vector3(1.0f, 1.0f, 1.0f));
}