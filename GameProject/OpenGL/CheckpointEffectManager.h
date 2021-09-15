/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class CheckpointEffect;
class Player;

class CheckpointEffectManager : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_objectTag アタッチしたゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	@param _playerPtr プレイヤーのポインタ
	*/
	CheckpointEffectManager(const Tag& _objectTag, SceneBase::Scene _sceneTag, Player* _playerPtr);

	/*
	@fn	デストラクタ
	*/
	~CheckpointEffectManager() {};

	/*
	@fn		エフェクトマネージャーのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
    @fn    速度を決める
    @param _quantity 個数
    */
	void DecideVelocity(const int _quantity);

	//ゲームオブジェクトクラスのポインタ
	GameObject* mOwner;
	//パーティクルの状態
	ParticleState	 mState;
	//シーンのタグ
	SceneBase::Scene mSceneTag;
	//アタッチしたゲームオブジェクトのタグ
	Tag				 mTag;
	//チェックポイントエフェクト
	CheckpointEffect* mCheckpointEffect;
	//プレイヤーのポインタ
	Player* mPlayer;

	//速度
	const float SPEED = 10.0f;
	//向き
	const float DIRECTION = 1.0f;
};

