/*
@brief プリプロセッサ
*/
#pragma once

class RippleClearEffect : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos 波紋のクリアエフェクトの生成場所
	@param	_Vel 波紋のクリアエフェクトの速度
	@param  _Color 波紋のクリアエフェクトのカラー値
	@param  _Scale スケール値
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	*/
	RippleClearEffect(const Vector3 _Pos, const Vector3 _Vel, const Vector3 _Color, const float _Scale, const Tag& _ObjectTag , const SceneBase::Scene _SceneTag);

	/*
	@fn	デストラクタ
	*/
	~RippleClearEffect() {};

	/*
	@fn	クリアエフェクトのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
};

