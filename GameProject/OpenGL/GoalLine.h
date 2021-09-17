/*
@brief プリプロセッサ
*/
#pragma once

class GoalLine : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos ゴールラインの座標
	@param	_Vel ゴールラインの速度
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	*/
	GoalLine(const Vector3& _Pos, const Vector3& _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	デストラクタ
	*/
	~GoalLine() {};

	/*
	@fn		操作方法パネルのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override {};

private:

};

