/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class CheckpointEffect;
class Player;

/*
@brief チェックポイントエフェクトの方向
*/
enum DirectionCheckpointEffect
{
	eRightCheckpoint = 0,
	eFrontCheckpoint = 1,
	eLeftCheckpoint = 2,
	eBackCheckpoint = 3,
	eRightFrontCheckpoint = 4,
	eLeftBackCheckpoint = 5,
	eRightBackCheckpoint = 6,
	eLeftFrontCheckpoint = 7
};

class CheckpointEffectManager : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	@param _playerPtr プレイヤーのポインタ
	*/
	CheckpointEffectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

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
    @param _Quantity 個数
    */
	void DecideVelocity(const int _Quantity);

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
};

