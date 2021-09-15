/*
@brief プリプロセッサ
*/
#pragma once

class AerialBlock : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 空中ブロックの座標
	@param	_size 空中ブロックのサイズ
	@param	_objectTag 空中ブロックのタグ
	@param	_sceneTag シーンのタグ
	*/
	AerialBlock(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~AerialBlock() {};

private:
};