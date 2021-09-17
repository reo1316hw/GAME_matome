/*
@brief プリプロセッサ
*/
#pragma once

class OperationExplanationBoard : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos 操作方法パネルの座標
	@param	_Vel 操作方法パネルの速度
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	*/
	OperationExplanationBoard(const Vector3& _Pos, const Vector3& _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

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

