/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class RightBlock : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 右移動ブロックの座標
	@param	_size 右移動ブロックのサイズ
	@param	_objectTag 右移動ブロックのタグ
	@param	_sceneTag シーンのタグ
	*/
	RightBlock(const Vector3& _pos, const Vector3& _size, const float _addEndPosX, const std::string _gpmeshName, const Tag& _objectTag, const ColliderTag& _colliderTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~RightBlock() {};

	/*
	@fn		右移動ブロックのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

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

	//全体の時間
	const float TOTAL_TIME = 1.0f;
	//右移動ブロックの右に移動する速度
	const float RIGHT_SPEED = 20.0f;
};