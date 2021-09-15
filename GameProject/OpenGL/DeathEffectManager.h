/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief インクルード
*/
#include "ParticleEffectBase.h"

/*
@brief 前方宣言
*/
class DeathEffect;
class Player;

class DeathEffectManager : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_objectTag アタッチしたゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	@param _playerPtr プレイヤーのポインタ
	*/
	DeathEffectManager(const Tag& _objectTag, SceneBase::Scene _sceneTag, Player* _playerPtr);

	/*
	@fn	デストラクタ
	*/
	~DeathEffectManager() {};

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
	//デスエフェクト
	DeathEffect* mDeathEffect;
	//プレイヤーのポインタ
	Player* mPlayer;
	// ランダムの速度
	Vector3 mRandVel;

	//任意のタイミングでデスエフェクトを生成するためのカウント
	int				 mCreateDeathEffectCount;

	//角度
	float			 mAngle;

	//デスエフェクトを一度だけ生成するためのフラグ
	bool			 OneCreateDeathFlag;
};

