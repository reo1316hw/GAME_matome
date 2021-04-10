/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/
#include "GameObject.h"

class AerialBlock : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos ゲームオブジェクトの座標
	@param	_size ゲームオブジェクトのサイズ
	@param	_objectTag ゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	*/
	AerialBlock(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~AerialBlock() {};

private:
};