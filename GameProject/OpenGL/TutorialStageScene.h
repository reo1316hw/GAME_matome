/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class VerticalMoveGroundExplanationBoard;
class OperationExplanationBoard;

class TutorialStageScene : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_NowScene 現在のシーン
	*/
	TutorialStageScene(const Scene& _NowScene);

	/*
	@fn	デストラクタ
	*/
	~TutorialStageScene();

	/*
	@fn    現在のシーン時に毎フレーム更新処理をする
	@param _KeyState 各入力機器の入力状態
	*/
	SceneBase* UpdateScene(const InputState& _KeyState) override;

private:

	//チュートリアルシーン中の縦移動床の説明パネル
	VerticalMoveGroundExplanationBoard* mVerticalMoveGroundExplanationBoard;
	//チュートリアルシーン中の操作説明パネル
	OperationExplanationBoard* mOperationExplanationBoard;
	//親ゴールラインのポインタ
	GoalLineRoot* mGoalLineRoot;
	//ゴールワープ板
	GoalWarpBorard* mGoalWarpBorard;

	// コンティニューシーンに移行するかのフラグ
	bool mTransitionFlag;
};