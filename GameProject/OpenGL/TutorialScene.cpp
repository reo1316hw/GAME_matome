/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_NowScene 現在のシーン
*/
TutorialScene::TutorialScene(const Scene& _NowScene)
	: mTransitionFlag(false)
{
	//環境光
	const Vector3 AmbientLight = Vector3(0.4f, 0.4f, 0.4f);
	//ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(AmbientLight);
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(0.0f, 1.0f, 0.0f);
	dir.m_diffuseColor = Vector3(0.5f, 0.6f, 0.8f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_NowScene);

	mSprite = new Sprite("Assets/forest.png");

	mMapCreate = new MapCreate();
	mPlayer = mMapCreate->OpenTutorialFile();

	//親ゴールラインの左上原点
	const Vector3 TopLeftOriginGoalLine = Vector3(300.0f, 200.0f, -75800.0f);
	//親ゴールラインを生成
	mGoalLineRoot = new GoalLineRoot(TopLeftOriginGoalLine, _NowScene, mPlayer);

	//操作説明ボード生成
	mOperationExplanationBoard = new OperationExplanationBoard(Vector3(0, 200, -96000), Vector3::sZERO, Tag::eOtherTag, _NowScene);
	//縦移動床説明ボード生成
	mVerticalMoveGroundExplanationBoard = new VerticalMoveGroundExplanationBoard(Vector3(0, 200, -92000), Vector3::sZERO, Tag::eOtherTag, _NowScene);

	//体力UI生成
	for (int i = 0; i < 3; i++)
	{
		mHeartUI = new HeartUI(Vector2(i * 100.0f, 50.0f), Tag::eOtherTag, Scene::eTutorial, mPlayer);
	}
}

/*
@fn	デストラクタ
*/
TutorialScene::~TutorialScene()
{
	GAME_OBJECT_MANAGER->RemoveSceneGameObject(Scene::eTutorial);
	delete mSprite;
	delete mMapCreate;
	delete mGoalLineRoot;
}

/*
@fn    現在のシーン時に毎フレーム更新処理をする
@param _KeyState 各入力機器の入力状態
*/
SceneBase* TutorialScene::UpdateScene(const InputState& _KeyState)
{
	//次のシーンに遷移するタイミング
	const int NextSceneTiming = 80;

	if (mPlayer->GetClearFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= NextSceneTiming)
		{
			return new Stage01Scene(Scene::eStage01);
		}
	}

	if (mPlayer->GetDeathFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= NextSceneTiming)
		{
			mTransitionFlag = true;
			return new ContinueScene(Scene::eContinue, Scene::eTutorial, mTransitionFlag);
		}
	}

	return this;
}