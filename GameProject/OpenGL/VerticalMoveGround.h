/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class Player;

class VerticalMoveGround : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos 縦移動床の座標
	@param	_Size 縦移動床のサイズ
	@param	_ObjectTag 縦移動床のタグ
	@param	_SceneTag シーンのタグ
	@param _playerPtr プレイヤーのポインタ
	*/
	VerticalMoveGround(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
	@fn	デストラクタ
	*/
	~VerticalMoveGround() {};

	/*
	@fn		縦移動床のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// プレイヤーのポインタ
	Player* mPlayer;

	/*
	@fn		縦移動床がヒットした時の処理
	@param	_hitObject ヒットした対象のゲームオブジェクトのアドレス
	*/
	void OnCollision(const GameObject& _HitObject)override;
};
