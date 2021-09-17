/*
@brief プリプロセッサ
*/
#pragma once

class SandEffect :public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos 砂ぼこりの座標
	@param	_Vel 砂ぼこりの速度
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	*/
	SandEffect(const Vector3 _Pos, const Vector3 _Vel, const SceneBase::Scene _SceneTag,const Tag& _ObjectTag);

	/*
	@fn	デストラクタ
	*/
	~SandEffect() {};

	/*
	@fn		砂ぼこりのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
};

