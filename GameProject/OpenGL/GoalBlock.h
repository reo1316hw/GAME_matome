/*
@brief プリプロセッサ
*/
#pragma once

class GoalBlock : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos ゴール柱の座標
	@param	_Size ゴール柱のサイズ
	@param	_ObjectTag ゴール柱のタグ
	@param	_SceneTag シーンのタグ
	*/
	GoalBlock(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	デストラクタ
	*/
	~GoalBlock() {};

private:

};