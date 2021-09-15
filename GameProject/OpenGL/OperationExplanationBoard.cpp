/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_pos 操作方法パネルの座標
@param	_vel 操作方法パネルの速度
@param	_objectTag アタッチしたゲームオブジェクトのタグ
@param	_sceneTag シーンのタグ
*/
OperationExplanationBoard::OperationExplanationBoard(const Vector3& _pos, const Vector3& _vel, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	:ParticleEffectBase(_pos, _vel, 0, "Assets/operation.png", _sceneTag, _objectTag)
{
	mInitPos = _pos;
	mScale = 400.0f;
	mAlpha = 1.0f;
	mParticle->SetScale(mScale);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Vector3(1.0f, 1.0f, 1.0f));
}