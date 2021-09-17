/*
@brief プリプロセッサ
*/
#pragma once

class ClearEffect : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos クリアエフェクトの生成場所
	@param	_Vel クリアエフェクトの速度
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	*/
	ClearEffect(const Vector3 _Pos, const Vector3 _Vel, const Tag& _ObjectTag , const SceneBase::Scene _SceneTag);

	/*
	@fn	デストラクタ
	*/
	~ClearEffect() {};

	/*
	@fn	クリアエフェクトのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
};

