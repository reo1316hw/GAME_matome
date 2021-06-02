/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class RightOneBlock_02 : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 1マス右移動床の座標
	@param	_size 1マス右移動床のサイズ
	@param	_objectTag 1マス右移動床のタグ
	@param	_sceneTag シーンのタグ
	*/
	RightOneBlock_02(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~RightOneBlock_02() {};

	/*
	@fn		1マス右移動床のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;
private:

	//1マス右移動床の右に移動する速度
	const float RIGHT_SPEED = 10.0f;
};