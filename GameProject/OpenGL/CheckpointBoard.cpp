/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos チェックポイントボードの座標
@param	_Vel チェックポイントボードの速度
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
*/
CheckpointBoard::CheckpointBoard(const Vector3& _Pos, const Vector3& _Vel, const std::string& _ParticleFileName ,const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:ParticleEffectBase(_Pos, _Vel, 0, _ParticleFileName, _SceneTag, _ObjectTag)
	, mCehckpointBoardAABB(Vector3::sZERO, Vector3::sZERO)
{
	mInitPos = _Pos;
	mScale = 3000.0f;
	mAlpha = 0.3f;
	mParticle->SetScale(mScale);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Color::sWHITE);

	mCehckpointBoardAABB = {Vector3(-1500.0f,-1500.0f,-100.0f),Vector3(1500.0f,1500.0f,100.0f)};

	mBoxcollider = new BoxCollider(this, ColliderTag::eCheckpoint, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mCehckpointBoardAABB);
}