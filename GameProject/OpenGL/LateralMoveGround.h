/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class Player;

class LateralMoveGround : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos 横移動床の座標
	@param	_Size 横移動床のサイズ
	@param	_ObjectTag 横移動床のタグ
	@param	_SceneTag シーンのタグ
	@param _distance 横移動床の移動する距離
    @param _playerPtr プレイヤーのポインタ
	*/
	LateralMoveGround(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, const float _Distance, Player* _playerPtr);

	/*
	@fn	デストラクタ
	*/
	~LateralMoveGround() {};

	/*
	@fn		横移動床のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	static Vector3 mSendVel;

	// プレイヤーのポインタ
	Player* mPlayer;

	//反転フラグ
	bool mReversFlag;

public://ゲッターセッター
	
	Vector3 GetVelocity() { return mSendVel; };
};