/*
@brief プリプロセッサ
*/
#pragma once

class Stage01Scene : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_NowScene 現在のシーン
	*/
	Stage01Scene(const Scene& _NowScene);

	/*
	@fn	デストラクタ
	*/
	~Stage01Scene();
 
	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* UpdateScene(const InputState& _State) override;

private:

	// コンティニューシーンに移行するかのフラグ
	bool mTransitionFlag;
};

