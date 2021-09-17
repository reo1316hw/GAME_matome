/*
@brief プリプロセッサ
*/
#pragma once

class Block : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos 障害物の座標
	@param	_Size 障害物のサイズ
	@param	_ObjectTag 障害物のタグ
	@param	_SceneTag シーンのタグ
	*/
	Block(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	デストラクタ
	*/
	~Block() {};

private:
};