/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class ClearEffect;
class Player;

class ClearEffectManager : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_owner ゲームオブジェクトクラスのポインタ
	@param	_objectTag アタッチしたゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	*/
	ClearEffectManager(GameObject* _owner, const Tag& _objectTag, SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~ClearEffectManager() {};

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
	ClearEffect* mClearEffect;
	//プレイヤーのポインタ
	Player* mPlayer;

	//速度
	const float SPEED = 10.0f;
	//向き
	const float DIRECTION = 1.0f;

	//クリアエフェクトを一度だけ生成するためのフラグ
	bool			 OneCreateClearFlag;
};