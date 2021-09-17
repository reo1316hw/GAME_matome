/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class TutorialScene;
class Stage01Scene;
class Stage02Scene;

class ContinueScene : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_NowScene 現在のシーン
	*/
	ContinueScene(const Scene& _NowScene, const Scene& _PreScene, const bool _TransitionSceneFlag);

	/*
	@fn	デストラクタ
	*/
	~ContinueScene();

	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* UpdateScene(const InputState& _State) override;

private:

	//チュートリアルシーンのポインタ
	TutorialScene*	  mTutorial;
	//ステージ01シーンのポインタ
	Stage01Scene* mStage01;
	//ステージ02シーンのポインタ
	Stage02Scene* mStage02;

	// チュートリアルに移行するかのフラグ
	bool mTutorialTransitionFlag;
	// ステージ1に移行するかのフラグ
	bool mStage01TransitionFlag;
	// ステージ2に移行するかのフラグ
	bool mStage02TransitionFlag;
};

