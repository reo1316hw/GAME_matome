/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class CheckpointBoard : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos チェックポイントボードの座標
	@param	_vel チェックポイントボード操作方法パネルの速度
	@param	_objectTag アタッチしたゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	*/
	CheckpointBoard(const Vector3& _pos, const Vector3& _vel, const std::string& _particleFileName ,const Tag& _objectTag, const SceneBase::Scene _sceneTag);

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