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
	ContinueScene(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~ContinueScene();

	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

private:

	//チュートリアルシーンのポインタ
	TutorialScene*	  mTutorial;
	//ステージ01シーンのポインタ
	Stage01Scene* mStage01;
	//ステージ02シーンのポインタ
	Stage02Scene* mStage02;
};

