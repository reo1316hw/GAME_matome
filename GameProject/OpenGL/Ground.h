/*
@brief プリプロセッサ
*/
#pragma once

class Ground : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos 床の座標
	@param	_Size 床のサイズ
	@param	_ObjectTag 床のタグ
	@param	_SceneTag シーンのタグ
	*/
	Ground(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	デストラクタ
	*/
	~Ground() {};

private:

};