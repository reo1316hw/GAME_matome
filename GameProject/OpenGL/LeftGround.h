/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class Player;

class LeftGround : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 1マス左移動床の座標
	@param	_size 1マス左移動床のサイズ
	@param	_objectTag 1マス左移動床のタグ
	@param	_sceneTag シーンのタグ
    @param _playerPtr プレイヤーのポインタ
	*/
	LeftGround(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag, Player* _playerPtr);

	/*
	@fn	デストラクタ
	*/
	~LeftGround() {};

	/*
	@fn		1マス左移動床のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// プレイヤーのポインタ
	Player* mPlayer;

	//1マス左移動床の左に移動する速度
	const float LEFT_SPEED = 10.0f;
};