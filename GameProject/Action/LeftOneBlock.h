/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class LeftOneBlock : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 1マス左移動床の座標
	@param	_size 1マス左移動床のサイズ
	@param	_objectTag 1マス左移動床のタグ
	@param	_sceneTag シーンのタグ
	*/
	LeftOneBlock(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~LeftOneBlock() {};

	/*
	@fn		1マス左移動床のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	//1マス左移動床の左に移動する速度
	const float LEFT_SPEED = 10.0f;
};