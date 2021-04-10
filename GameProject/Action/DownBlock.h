/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/
#include "GameObject.h"

class DownBlock : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos ゲームオブジェクトの座標
	@param	_size ゲームオブジェクトのサイズ
	@param	_objectTag ゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	*/
	DownBlock(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~DownBlock() {};

	/*
	@fn		ゲームオブジェクトのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	const float DOWN_SPEED = 20;

};