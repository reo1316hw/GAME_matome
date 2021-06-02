/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class VerticalMoveGround : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 縦移動床の座標
	@param	_size 縦移動床のサイズ
	@param	_objectTag 縦移動床のタグ
	@param	_sceneTag シーンのタグ
	*/
	VerticalMoveGround(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~VerticalMoveGround() {};

	/*
	@fn		縦移動床のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	//縦移動床の前に移動する速度
	const float FORWARD_SPEED = 10.0f;

	/*
	@fn		縦移動床がヒットした時の処理
	@param	_hitObject ヒットした対象のゲームオブジェクトのアドレス
	*/
	void OnCollision(const GameObject& _hitObject)override;
};
