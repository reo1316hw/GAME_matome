/*
@brief プリプロセッサ
*/
#pragma once

class GoalWarpHole : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos ゴールワ－プホールの座標
	@param	_Size ゴールワ－プホールのサイズ
	@param	_ObjectTag ゴールワ－プホールのタグ
	@param	_SceneTag シーンのタグ
	@param  _playerPtr プレイヤーのポインタ
	*/
	GoalWarpHole(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
	@fn	デストラクタ
	*/
	~GoalWarpHole() {};

private:
};

