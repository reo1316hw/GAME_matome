/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class ClearEffect;
class Player;

/*
@brief クリアエフェクトの方向
*/
enum DirectionClearEffect
{
	eLeftUpClear = 0,
	eLeftUpUpClear = 1,
	eUpClear = 2,
	eRightUpUpClear = 3,
	eRightUpClear = 4
};

class ClearEffectManager : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	@param _playerPtr プレイヤーのポインタ
	*/
	ClearEffectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

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
	ClearEffect* mClearEffect;
	//プレイヤーのポインタ
	Player* mPlayer;

	//クリアエフェクトを一度だけ生成するためのフラグ
	bool			 OneCreateClearFlag;
};