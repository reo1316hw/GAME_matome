/*
@brief プリプロセッサ
*/
#pragma once

class CheckpointBoard : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos チェックポイントボードの座標
	@param	_Vel チェックポイントボード操作方法パネルの速度
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	*/
	CheckpointBoard(const Vector3& _Pos, const Vector3& _Vel, const std::string& _ParticleFileName ,const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	デストラクタ
	*/
	~CheckpointBoard() {};

	/*
	@fn		操作方法パネルのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override {};

private:

	AABB mCehckpointBoardAABB;
};