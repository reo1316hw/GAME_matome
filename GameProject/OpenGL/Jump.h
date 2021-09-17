/*
@brief プリプロセッサ
*/
#pragma once

class Jump : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos ジャンプ床の座標
	@param	_Size ジャンプ床のサイズ
	@param	_ObjectTag ジャンプ床のタグ
	@param	_SceneTag シーンのタグ
	*/
	Jump(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
	@fn	デストラクタ
	*/
	~Jump() {};

	/*
	@fn		ジャンプ床のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn		ジャンプ床がヒットした時の処理
	@param	_HitObject ヒットした対象のゲームオブジェクトのアドレス
	*/
	void OnCollision(const GameObject& _HitObject)override;

private:

	// プレイヤーのポインタ
	Player* mPlayer;

	//角度
	float degree;
};