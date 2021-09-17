/*
@briefプリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class Player;
class InvisibleMeshComponent;

class Glass : public GameObject
{
public:

	/*
	@fn	   コンストラクタ
	@param _Pos ガラス床の座標
	@param _Size ガラス床のサイズ
	@param _ObjectTag ガラス床のタグ
	@param _SceneTag シーンのタグ
	@param _playerPtr プレイヤーのポインタ
	*/
	Glass(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
	@fn	デストラクタ
	*/
	~Glass() {};

	/*
	@fn		ガラス床のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	//ガラス床のアルファブレンドメッシュ
	InvisibleMeshComponent* mInvisibleMeshComponent;

	// プレイヤーのポインタ
	Player* mPlayer;

	//落ちるまでのカウント
	int mDownCount;

	/*
	@fn		ガラス床がヒットした時の処理
	@param	_HitObject ヒットした対象のゲームオブジェクトのアドレス
	*/
	void OnCollision(const GameObject& _HitObject)override;
};