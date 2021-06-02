/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class VerticalMoveGroundExplanationBoard;
class OperationExplanationBoard;

class TutorialScene : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	TutorialScene(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~TutorialScene();

	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

	static bool GetContinueTutorialFlag() { return mSendContinueTutorialFlag; };
	static void SetContinueTutorialFlag(bool _continue) { mSendContinueTutorialFlag = _continue; };

private:

	//チュートリアルシーン中の縦移動床の説明パネル
	VerticalMoveGroundExplanationBoard* mVerticalMoveGroundExplanationBoard;
	//チュートリアルシーン中の操作説明パネル
	OperationExplanationBoard* mOperationExplanationBoard;

	static bool mSendContinueTutorialFlag;

	//コンティニューシーンに移行するかのフラグ
	bool mContinueTutorialFlag;
};

