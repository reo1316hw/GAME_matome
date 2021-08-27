/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class Respawn : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos リスポーン地点の座標
	@param	_size リスポーン地点のサイズ
	@param	_objectTag リスポーン地点のタグ
	@param	_sceneTag シーンのタグ
	*/
	Respawn(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~Respawn() {};

private:
};