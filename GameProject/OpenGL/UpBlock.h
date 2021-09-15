/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class Player;

class UpBlock : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 上移動ブロックの座標
	@param	_size 上移動ブロックのサイズ
	@param	_objectTag 上移動ブロックのタグ
	@param	_sceneTag シーンのタグ
	@param _playerPtr プレイヤーのポインタ
	*/
	UpBlock(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag, Player* _playerPtr);

	/*
	@fn	デストラクタ
	*/
	~UpBlock() {};

	/*
	@fn		上移動ブロックのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// プレイヤーのポインタ
	Player* mPlayer;

	//上移動ブロックの上に移動する速度
	const float UP_SPEED = 10.0f;
};