/*
@brief プリプロセッサ
*/
#pragma once

class VerticalMoveGroundExplanationBoard : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos 縦移動床の説明パネルの座標
	@param	_Vel 縦移動床の説明パネルの速度
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	*/
	VerticalMoveGroundExplanationBoard(const Vector3& _Pos, const Vector3& _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	デストラクタ
	*/
	~VerticalMoveGroundExplanationBoard() {};

	/*
	@fn		縦移動床の説明パネルのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override {};

private:

};

