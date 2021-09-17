/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class VerticalMoveGroundExplanationBoard;
class OperationExplanationBoard;

class TutorialScene : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_NowScene 現在のシーン
	*/
	TutorialScene(const Scene& _NowScene);

	/*
	@fn	デストラクタ
	*/
	~TutorialScene();

	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* UpdateScene(const InputState& _State) override;

private:

	//チュートリアルシーン中の縦移動床の説明パネル
	VerticalMoveGroundExplanationBoard* mVerticalMoveGroundExplanationBoard;
	//チュートリアルシーン中の操作説明パネル
	OperationExplanationBoard* mOperationExplanationBoard;

	// コンティニューシーンに移行するかのフラグ
	bool mTransitionFlag;
};