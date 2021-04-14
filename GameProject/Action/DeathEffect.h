/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/
#include "ParticleEffectBase.h"

class DeathEffect : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos デスエフェクトの生成場所
	@param	_vel クリアエフェクトの速度
	@param	_objectTag アタッチしたゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	*/
	DeathEffect(Vector3 _pos, Vector3 _vel, const Tag& _objectTag, SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~DeathEffect() {};

	/*
	@fn		デスエフェクトのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

};

