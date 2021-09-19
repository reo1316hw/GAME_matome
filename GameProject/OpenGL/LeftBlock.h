/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class Player;

class LeftBlock : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos 左移動床の座標
	@param	_Size 左移動床のサイズ
	@param	_ObjectTag 左移動床のタグ
	@param	_SceneTag シーンのタグ
	@param _playerPtr プレイヤーのポインタ
	*/
	LeftBlock(const Vector3& _Pos, const Vector3& _Size, const float _AddPosX, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
	@fn	デストラクタ
	*/
	~LeftBlock() {};

	/*
	@fn		左移動床のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// プレイヤーのポインタ
	Player* mPlayer;
	//反転する座標
	Vector3 mInversionPos;

	//揺れるか
	bool mShakeFlag;
	//反転するか
	bool mReversFlag;

	//時間(進行度)
	float mElapseTime;
	//開始と終了の値の差分
	float mDifferencePos;
	//開始の値
	float mStart;
};