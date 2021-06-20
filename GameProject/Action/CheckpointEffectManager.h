/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class CheckpointEffect;
class Player;

class CheckpointEffectManager : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_owner ゲームオブジェクトクラスのポインタ
	@param	_objectTag アタッチしたゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	*/
	CheckpointEffectManager(GameObject* _owner, const Tag& _objectTag, SceneBase::Scene _sceneTag);

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

	bool a;
};

