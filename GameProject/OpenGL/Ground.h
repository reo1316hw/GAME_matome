/*
@brief プリプロセッサ
*/
#pragma once

class Ground : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 床の座標
	@param	_size 床のサイズ
	@param	_objectTag 床のタグ
	@param	_sceneTag シーンのタグ
	*/
	Ground(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~Ground() {};

private:

};