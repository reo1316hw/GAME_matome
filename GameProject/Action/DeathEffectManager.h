/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

#include "ParticleEffectBase.h"

class DeathEffect;
class Player;

class DeathEffectManager : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_owner ゲームオブジェクトクラスのポインタ
	@param	_objectTag アタッチしたゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	*/
	DeathEffectManager(GameObject* _owner, const Tag& _objectTag, SceneBase::Scene _sceneTag);

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

	//任意のタイミングでデスエフェクトを生成するためのカウント
	int				 mCreateDeathEffectCount;

	//角度
	float			 mAngle;

	//デスエフェクトを一度だけ生成するためのフラグ
	bool			 OneCreateDeathFlag;
};

