/*
@brief プリプロセッサ
*/
#pragma once

class HeartUI :public UIBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos プレイヤーの体力UIの生成場所(スクリーン座標)
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	@param _playerPtr プレイヤーのポインタ
	*/
	HeartUI(const Vector2& _Pos, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
	@fn	デストラクタ
	*/
	~HeartUI() {};

	/*
	@fn		プレイヤーの体力UIのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
};