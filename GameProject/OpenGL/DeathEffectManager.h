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

/*
@brief デスエフェクトの方向
*/
enum DirectionDeathEffect
{
	eLeftDeath = 0,
	eBackDeath = 1,
	eLeftBackDeath = 2
};

class DeathEffectManager : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	@param _playerPtr プレイヤーのポインタ
	*/
	DeathEffectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

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

