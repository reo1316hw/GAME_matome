/*
@brief プリプロセッサ
*/
#pragma once

class FirstStageScene : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_NowScene 現在のシーン
	*/
	FirstStageScene(const Scene& _NowScene);

	/*
	@fn	デストラクタ
	*/
	~FirstStageScene();
 
	/*
	@fn    現在のシーン時に毎フレーム更新処理をする
	@param _KeyState 各入力機器の入力状態
	*/
	SceneBase* UpdateScene(const InputState& _KeyState) override;

private:

	//親ゴールラインのポインタ
	GoalLineRoot* mGoalLineRoot;
	//ゴールワープ板
	GoalWarpBorard* mGoalWarpBorard;

	// コンティニューシーンに移行するかのフラグ
	bool mTransitionFlag;
};

