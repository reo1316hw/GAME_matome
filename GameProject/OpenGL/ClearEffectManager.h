/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class RippleClearEffect;
class Player;

/*
@brief クリアエフェクトの方向
*/
enum DirectionClearEffect
{
	eLeftUnderClear = 0,
	eRightUpClear = 1,
	eLeftUpClear = 2,
	eRightUnderClear = 3,
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
	@fn 粒子のクリアエフェクト生成
	*/
	void CreateParticleClearEffect();

	/*
	@fn 波紋のクリアエフェクト生成
	*/
	void CreateRippleClearEffect();

	/*
	@fn 速度を決める
	*/
	void DecideVelocity();

	//ゲームオブジェクトクラスのポインタ
	GameObject* mOwner;
	//パーティクルの状態
	ParticleState	 mState;
	//シーンのタグ
	SceneBase::Scene mSceneTag;
	//アタッチしたゲームオブジェクトのタグ
	Tag				 mTag;
	//チェックポイントエフェクト
	RippleClearEffect* mRippleClearEffect;
	//プレイヤーのポインタ
	Player* mPlayer;

	//クリアエフェクトを一度だけ生成するためのフラグ
	bool OneCreateClearFlag;
	//角度
	float mAngle;

	//生成するタイミングのカウント
	int mCreateTimingCount;
	//生成した数をカウント
	int mCreateCount;
};