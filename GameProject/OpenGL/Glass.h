/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

// 前方宣言
class Player;

class InvisibleMeshComponent;

class Glass : public GameObject
{
public:

	/*
	@fn	   コンストラクタ
	@param _pos ガラス床の座標
	@param _size ガラス床のサイズ
	@param _objectTag ガラス床のタグ
	@param _sceneTag シーンのタグ
	@param _playerPtr プレイヤーのポインタ
	*/
	Glass(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag, Player* _playerPtr);

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

	// プレイヤーのポインタ
	Player* mPlayer;

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