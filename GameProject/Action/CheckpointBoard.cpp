/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_pos チェックポイントボードの座標
@param	_vel チェックポイントボードの速度
@param	_objectTag アタッチしたゲームオブジェクトのタグ
@param	_sceneTag シーンのタグ
*/
CheckpointBoard::CheckpointBoard(const Vector3& _pos, const Vector3& _vel, const std::string& _particleFileName ,const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	:ParticleEffectBase(_pos, _vel, 0, _particleFileName, _sceneTag, _objectTag)
	, mCehckpointBoardAABB(Vector3::Zero, Vector3::Zero)
{
	mScale = 3000.0f;
	mAlpha = 0.3f;
	mParticle->SetScale(mScale);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Vector3(1.0f, 1.0f, 1.0f));

	mCehckpointBoardAABB = {Vector3(-1500.0f,-1500.0f,0.0f),Vector3(1500.0f,1500.0f,1.0f)};

	mBoxcollider = new BoxCollider(this, ColliderTag::checkpoint, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mCehckpointBoardAABB);
}

/*
@fn		操作方法パネルのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void CheckpointBoard::UpdateGameObject(float _deltaTime)
{
	/*ParticleEffectBase::LifeCountDown();

	if (lifeCount >= 0)
	{
		position += velocity * 10.0f;

		mScale += 5.0f;
		mAlpha -= 0.05f;
		particle->SetScale(mScale);
		particle->SetAlpha(mAlpha);
		SetPosition(position);
	}

	if (lifeCount <= 0)
	{
		state = State::Dead;
	}*/
}
