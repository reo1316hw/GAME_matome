/*
@brief プリプロセッサ
*/
#pragma once

class TitleScene : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_NowScene 現在のシーン
	*/
	TitleScene(const Scene& _NowScene);

	/*
	@fn	デストラクタ
	*/
	~TitleScene();

	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* UpdateScene(const InputState& _State) override;

private:
};

