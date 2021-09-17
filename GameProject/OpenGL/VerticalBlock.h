/*
@brief プリプロセッサ
*/
#pragma once

class VerticalBlock : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos 縦長障害物の座標
	@param	_Size 縦長障害物のサイズ
	@param	_ObjectTag 縦長障害物のタグ
	@param	_SceneTag シーンのタグ
	*/
	VerticalBlock(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	デストラクタ
	*/
	~VerticalBlock() {};

private:
};