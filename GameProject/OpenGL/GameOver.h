/*
@brief プリプロセッサ
*/
#pragma once

class GameOver : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_NowScene 現在のシーン
	*/
	GameOver(const Scene& _NowScene);

	/*
	@fn	デストラクタ
	*/
	~GameOver();

	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* UpdateScene(const InputState& _State) override;

private:
};

