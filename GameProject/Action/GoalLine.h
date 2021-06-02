/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class GoalLine : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos ゴールラインの座標
	@param	_vel ゴールラインの速度
	@param	_objectTag アタッチしたゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	*/
	GoalLine(const Vector3& _pos, const Vector3& _vel, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~GoalLine() {};

	/*
	@fn		ゴールラインのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

};

