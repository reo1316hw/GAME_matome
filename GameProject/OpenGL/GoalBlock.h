/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class GoalBlock : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos ゴール柱の座標
	@param	_size ゴール柱のサイズ
	@param	_objectTag ゴール柱のタグ
	@param	_sceneTag シーンのタグ
	*/
	GoalBlock(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~GoalBlock() {};

private:

};