/*
@brief プリプロセッサ
*/
#pragma once

class CheckpointEffect : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos クリアエフェクトの生成場所
	@param	_vel クリアエフェクトの速度
	@param	_objectTag アタッチしたゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	*/
	CheckpointEffect(Vector3 _pos, Vector3 _vel, const Tag& _objectTag, SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~CheckpointEffect() {};

	/*
	@fn	クリアエフェクトのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	//速度の初期値
	const float VELOCITY_INITIAL_VALUE = 30.0f;
	//速度の減速値
	const float VELOCITY_MINUS_VALUE = 1.5f;
	//加速度の初期値
	const float ACCELERATION_INITIAL_VALUE = 1.0f;
	//透明度の初期値
	const float ALPHA_INITIAL_VALUE = 1.0f;
	//スケールの初期値
	const float SCALE_INITIAL_VALUE = 0.0f;
	//スケールの加速値
	const float SCALE_PLUS_VALUE = 4.0f;
	//スケールの最大値
	const float SCALE_MAX_VALUE = 64.0f;
};