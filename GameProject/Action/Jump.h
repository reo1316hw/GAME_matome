/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class Jump : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos ジャンプ床の座標
	@param	_size ジャンプ床のサイズ
	@param	_objectTag ジャンプ床のタグ
	@param	_sceneTag シーンのタグ
	*/
	Jump(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~Jump() {};

	/*
	@fn		ジャンプ床のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn		ジャンプ床がヒットした時の処理
	@param	_hitObject ヒットした対象のゲームオブジェクトのアドレス
	*/
	void OnCollision(const GameObject& _hitObject)override;

private:

	//角度
	float degree;
};