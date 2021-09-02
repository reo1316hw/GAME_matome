/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

#include "ParticleEffectBase.h"

class SandEffect;
class DeathEffect;
class ClearEffect;
class CheckpointEffect;
class Player;

class SandEffectManager : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_owner ゲームオブジェクトクラスのポインタ
	@param	_objectTag アタッチしたゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	*/
	SandEffectManager(GameObject* _owner, const Tag& _objectTag, SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~SandEffectManager() {};

	/*
	@fn		エフェクトマネージャーのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;
	
private:

	//ゲームオブジェクトクラスのポインタ
	GameObject*		 mOwner;
	//パーティクルの状態
	ParticleState	 mState;
	//エフェクトマネージャーの座標
	Vector3			 mPos;
	//シーンのタグ
	SceneBase::Scene mSceneTag;
	//アタッチしたゲームオブジェクトのタグ
	Tag				 mTag;
	//砂ぼこりエフェクト
	SandEffect*		 mSandEffect;

	//任意のタイミングで砂ぼこりエフェクトを生成するためのカウント
	int				 mCreateSandEffectCount;
};

