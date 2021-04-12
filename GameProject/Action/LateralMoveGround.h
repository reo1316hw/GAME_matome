/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/
#include "GameObject.h"

class LateralMoveGround : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 横移動床の座標
	@param	_size 横移動床のサイズ
	@param	_objectTag 横移動床のタグ
	@param	_sceneTag シーンのタグ
	@param _distance 横移動床の移動する距離
	*/
	LateralMoveGround(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const float _distance);

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



	//反転フラグ
	bool mReversFlag;

public://ゲッターセッター
	


	Vector3 GetVelocity() { return mSendVel; };



};