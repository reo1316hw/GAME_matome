/*
@brief プリプロセッサ
*/
#pragma once

class AerialBlock : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos 空中ブロックの座標
	@param	_Size 空中ブロックのサイズ
	@param	_ObjectTag 空中ブロックのタグ
	@param	_SceneTag シーンのタグ
	*/
	AerialBlock(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/*
	@fn	デストラクタ
	*/
	~AerialBlock() {};

private:
};