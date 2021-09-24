/*
@brief プリプロセッサ
*/
#pragma once

class GoalCircleFrame : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos ゴール円の枠の座標
	@param	_Size ゴール円の枠のサイズ
	@param	_ObjectTag ゴール円の枠のタグ
	@param	_SceneTag シーンのタグ
	*/
	GoalCircleFrame(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	デストラクタ
	*/
	~GoalCircleFrame() {};

private:
};

