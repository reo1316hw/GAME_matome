/*
@brief プリプロセッサ
*/
#pragma once

class Stage01Scene : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	Stage01Scene(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~Stage01Scene();
 
	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update(const InputState& _state) override;

private:

	// コンティニューシーンに移行するかのフラグ
	bool mTransitionFlag;
};

