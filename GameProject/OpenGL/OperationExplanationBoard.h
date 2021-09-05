/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class OperationExplanationBoard : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 操作方法パネルの座標
	@param	_vel 操作方法パネルの速度
	@param	_objectTag アタッチしたゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	*/
	OperationExplanationBoard(const Vector3& _pos, const Vector3& _vel, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~OperationExplanationBoard() {};

	/*
	@fn		操作方法パネルのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override {};

private:
};

