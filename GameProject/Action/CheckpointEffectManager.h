/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/
#include "ParticleEffectBase.h"

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

	//任意のタイミングでチェックポイントエフェクトを生成するためのカウント
	int				 mCreateCheckpointEffectCount;

	//チェックポイントエフェクトを生成するかのフラグ
	bool			 mCheckpointFlag;

	const float SPEED = 5.0f;
	const float DIRECTION = 1.0f;
};

