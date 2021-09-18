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
    @fn	チェックポイントを制御
    */
	void CheckpointEffectControl();

	//地面のY座標
	const float MGroundYPos;

	//プレイヤーの球当たり判定を生成
	SphereCollider*		mSelfSphereCollider;
	//プレイヤーの球当たり判定の大きさ
	Sphere				mPlayerSphere;
	//プレイヤーの砂ぼこりエフェクト
	SandEffectManager*  mSandEffectManager;
	//プレイヤーのクリアエフェクト
	ClearEffectManager* mClearEffectManager;
	//プレイヤーのデスエフェクト
	DeathEffectManager* mDeathEffectManager;
	//プレイヤーのチェックポイントエフェクト
	CheckpointEffectManager* mCheckpointEffectManager;
	//横移動床のポインタ
	LateralMoveGround*	mLateral;
	//横移動床にあたった時の速度
	Vector3				mLateralMoveVelocity;

	//死んだか
	bool		mDeathFlag;
	//ダメージを受けたか
	bool		mDamageFlag;
	//リスポーン後の待機フラグ
	bool		mStopFlag;
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
	
	/*
	@fn		プレイヤーがヒットした時の処理
	@param	_HitObject ヒットした対象のゲームオブジェクトのアドレス
	*/
	void OnCollision(const GameObject& _HitObject)override;

public://ゲッターセッター

	bool GetClearFlag() { return mClearFlag; };
	bool GetDeathFlag() { return mDeathFlag; };
    bool GetEnableCheckpointFlag() { return mEnableCheckpointFlag; };
    int GetLife() { return mLife; };

};

