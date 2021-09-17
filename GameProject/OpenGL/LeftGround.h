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
	@param	_Pos 1マス左移動床の座標
	@param	_Size 1マス左移動床のサイズ
	@param	_ObjectTag 1マス左移動床のタグ
	@param	_SceneTag シーンのタグ
    @param _playerPtr プレイヤーのポインタ
	*/
	LeftGround(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

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
};