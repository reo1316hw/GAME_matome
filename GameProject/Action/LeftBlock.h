/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/
#include "GameObject.h"

class LeftBlock : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 左移動床の座標
	@param	_size 左移動床のサイズ
	@param	_objectTag 左移動床のタグ
	@param	_sceneTag シーンのタグ
	*/
	LeftBlock(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

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

	//左移動床の左に移動する速度
	const float LEFT_SPEED = 20;
};