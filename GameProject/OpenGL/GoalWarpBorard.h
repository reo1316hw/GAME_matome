/*
@brief プリプロセッサ
*/
#pragma once

class GoalWarpBorard : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos ゴールワープ板の座標
	@param	_Vel ゴールワープ板の速度
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	*/
	GoalWarpBorard(const Vector3& _Pos, const Vector3& _Vel, const std::string& _ParticleFileName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	デストラクタ
	*/
	~GoalWarpBorard() {};

	/*
	@fn		ゴールワープ板のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	//角度
	float mAngle;
};