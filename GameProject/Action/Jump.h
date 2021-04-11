/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/
#include "GameObject.h"

class Jump : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos ジャンプ床の座標
	@param	_size ジャンプ床のサイズ
	@param	_objectTag ジャンプ床のタグ
	@param	_sceneTag シーンのタグ
	*/
	Jump(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~Jump() {};

private:

};