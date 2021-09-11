/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class TutorialScene;
class Stage01Scene;
class Stage02Scene;

class ContinueScene : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	ContinueScene(const Scene& _nowScene, const Scene& _preScene, const bool _transitionSceneFlag);

	/*
	@fn	デストラクタ
	*/
	~ContinueScene();

	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update(const InputState& _state) override;

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

