/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class VerticalBlock : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 縦長障害物の座標
	@param	_size 縦長障害物のサイズ
	@param	_objectTag 縦長障害物のタグ
	@param	_sceneTag シーンのタグ
	*/
	VerticalBlock(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~VerticalBlock() {};

private:

};