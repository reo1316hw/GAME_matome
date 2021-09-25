/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief インクルード
*/
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@brief 前方宣言
*/
class SandEffectManager;
class ClearEffectManager;
class DeathEffectManager;
class CheckpointEffectManager;
class SphereCollider;
class LateralMoveGround;
class GoalLineRoot;
class GoalWarpHole;

/*
@brief 表示非表示
*/
enum VisibleType
{
	eInvisible = 0,
	eVisible = 5
};

class Player:public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos プレイヤーの座標
	@param	_Size プレイヤーのサイズ
	@param	_ObjectTag プレイヤーのタグ
	@param	_SceneTag シーンのタグ
	*/
	Player(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	デストラクタ
	*/
	~Player() {};

	/*
	@fn		プレイヤーのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn		入力を引数で受け取る更新関数
	@brief	基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
	@param	_KeyState 各入力機器の入力状態
	@brief	キーボード、マウス、コントローラー
	*/
	void GameObjectInput(const InputState& _KeyState)override;

private:

	/*
	@fn コントローラー入力処理
	@param	_KeyState 各入力機器の入力状態
	*/
	void InputController(const InputState& _KeyState);

	/*
	@fn アナログスティック入力処理
	@param	_KeyState 各入力機器の入力状態
	*/
	void InputStick(const InputState& _KeyState);

	/*
    @fn	チェックポイントエフェクトを制御
    */
	void CheckpointEffectControl();

	/*
    @fn		プレイヤーがヒットした時の処理
    @param	_HitObject ヒットした対象のゲームオブジェクトのアドレス
    */
	void OnCollision(const GameObject& _HitObject)override;

	/*
	@fn	    チェックポイントに当たった時の処理
	@param	_HitObject ヒットした対象のゲームオブジェクトのアドレス
	*/
	void HitCheckPoint(const GameObject& _HitObject);

	//地面のY座標
	const float MGroundYPos;

	//加速度
	const float MPlayerSpeedUp;

	//プレイヤーの球当たり判定を生成
	SphereCollider* mSelfSphereCollider;
	//プレイヤーの球当たり判定の大きさ
	Sphere mPlayerSphere;
	//プレイヤーの砂ぼこりエフェクト
	SandEffectManager* mSandEffectManager;
	//プレイヤーのクリアエフェクト
	ClearEffectManager* mClearEffectManager;
	//プレイヤーのデスエフェクト
	DeathEffectManager* mDeathEffectManager;
	//プレイヤーのチェックポイントエフェクト
	CheckpointEffectManager* mCheckpointEffectManager;
	//横移動床のポインタ
	LateralMoveGround* mLateral;
	//親ゴールラインのポインタ
	GoalLineRoot* mGoalLineRoot;
	//ゴールワープホールのポインタ
	GoalWarpHole* mGoalWarpHole;
	//横移動床にあたった時の速度
	Vector3		  mLateralMoveVelocity;
	//クリアのz地点
	Vector3       mClearPos;

	//死んだか
	bool		mDeathFlag;
	//ダメージを受けたか
	bool		mDamageFlag;
	//リスポーン後の待機フラグ
	bool		mStopFlag;		
	//ゴール演出するか
	bool        mGoalProductionFlag;
	//クリアしたか
	bool		mClearFlag;
	//ジャンプするか
	bool		mJumpFlag;
	//スケールを変えるか
	bool		mScaleFlag;
	//ボタンが入力されたか
	bool		mButtonFlag;
	//接地したか
	bool		mGroundFlag;
	//当たり判定を行うか
	bool		mCollisionFlag;
	//チェックポイントを有効にするか
	bool		mEnableCheckpointFlag;
	//チェックポイントボードに当たったか
	bool		mHitCheckpointFlag;
	// リスポーンしたか
	bool        mRespawnFlag;
	//1回だけ親ゴールラインのポインタを取得するためのフラグ
	bool        mGetGoalLineRootFlag;
	//1回だけゴールワープホールのポインタを取得するためのフラグ
	bool        mGetGoalWarpHoleFlag;

	//プレイヤーが点滅するためのカウント
	int			mVisibleFrameCount;
	//現在のシーンはどれか
	int			mScene;
	//体力	
	int			mLife;
	//チェックポイントエフェクトを生存時間
	int			mCheckpointEffectCount;
	//角度
	float		mAngle;
	//ゴールz座標
	float       mGoalZPos;

public://ゲッターセッター

	bool GetGoalProductionFlag() { return mGoalProductionFlag; };
	bool GetClearFlag() { return mClearFlag; };
	bool GetDeathFlag() { return mDeathFlag; };
    bool GetEnableCheckpointFlag() { return mEnableCheckpointFlag; };
    int  GetLife() { return mLife; };

	/*
	@param _lateralMoveGroundPtr 横移動床のポインタ
	*/
	void SetLateralMoveGroundPtr(LateralMoveGround* _lateralMoveGroundPtr) { mLateral = _lateralMoveGroundPtr; };
	/*
	@param	_goalLineRootPtr 親ゴールラインのポインタ
	*/
	void SetGoalLineRoot(GoalLineRoot* _goalLineRootPtr) { mGoalLineRoot = _goalLineRootPtr; };
	/*
	@param	_goalWarpHole ゴールワープホールのポインタ
	*/
	void SetGoalWarpHolePtr(GoalWarpHole* _goalWarpHole) { mGoalWarpHole = _goalWarpHole; };
};

