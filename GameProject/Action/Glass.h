/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class InvisibleMeshComponent;

class Glass : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos ガラス床の座標
	@param	_size ガラス床のサイズ
	@param	_objectTag ガラス床のタグ
	@param	_sceneTag シーンのタグ
	*/
	Glass(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~Glass() {};

	/*
	@fn		ガラス床のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	//ガラス床のアルファブレンドメッシュ
	InvisibleMeshComponent* mInvisibleMeshComponent;

	//落ちるまでのカウント
	int mDownCount;

	// 落ちるスピード
	const float DOWN_SPEED = 100.0f;

	/*
	@fn		ガラス床がヒットした時の処理
	@param	_hitObject ヒットした対象のゲームオブジェクトのアドレス
	*/
	void OnCollision(const GameObject& _hitObject)override;
};