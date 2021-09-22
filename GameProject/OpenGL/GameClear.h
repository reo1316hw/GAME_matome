/*
@brief プリプロセッサ
*/
#pragma once

class GameClear : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_NowScene 現在のシーン
	*/
	GameClear(const Scene& _NowScene);

	/*
	@fn	デストラクタ
	*/
	~GameClear();

	/*
	@fn    現在のシーン時に毎フレーム更新処理をする
	@param _KeyState 各入力機器の入力状態
	*/
	SceneBase* UpdateScene(const InputState& _KeyState) override;

private:

};

