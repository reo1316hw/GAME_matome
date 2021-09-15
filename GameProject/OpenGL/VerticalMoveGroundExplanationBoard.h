/*
@brief プリプロセッサ
*/
#pragma once

class VerticalMoveGroundExplanationBoard : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 縦移動床の説明パネルの座標
	@param	_vel 縦移動床の説明パネルの速度
	@param	_objectTag アタッチしたゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	*/
	VerticalMoveGroundExplanationBoard(const Vector3& _pos, const Vector3& _vel, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~VerticalMoveGroundExplanationBoard() {};

	/*
	@fn		操作方法パネルのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override {};

private:

};

