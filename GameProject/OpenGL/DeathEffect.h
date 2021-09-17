/*
@brief プリプロセッサ
*/
#pragma once

class DeathEffect : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos デスエフェクトの生成場所
	@param	_Vel クリアエフェクトの速度
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	*/
	DeathEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

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

