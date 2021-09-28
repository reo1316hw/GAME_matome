/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_NowScene 現在のシーン
*/
SecondStageScene::SecondStageScene(const Scene& _NowScene)
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

	mSprite = new Sprite("Assets/BackGround/SecondStage.png");

	mMapCreate = new MapCreate();
	mPlayer = mMapCreate->OpenStage02File();

	//親ゴールラインの左上原点
	const Vector3 TopLeftOriginGoalLine = Vector3(300.0f, 200.0f, -2200.0f);
	//親ゴールラインを生成
	mGoalLineRoot = new GoalLineRoot(TopLeftOriginGoalLine, _NowScene, mPlayer);

	//チェックポイントボード生成
	for (int i = 0; i < 3; i++)
	{
		if (i <= 1)
		{
			mCheckPointBoard = new CheckpointBoard(Vector3(800.0f, 500.0f, (-83100.0f + i * 22000.0f)), Vector3::sZERO, "Assets/Texture/Board/SecondStageCheckpoint.png", Tag::eCheckpointTag, _NowScene);
		}
		else
		{
			mCheckPointBoard = new CheckpointBoard(Vector3(800.0f, 500.0f, -29100.0f), Vector3::sZERO, "Assets/Texture/Board/SecondStageCheckpoint.png", Tag::eCheckpointTag, _NowScene);
		}
	}

	//ゴールワープ板生成
	mGoalWarpBorard = new GoalWarpBorard(Vector3(800.0f, 350.0f, -1000.0f), Vector3::sZERO, "Assets/Texture/Board/Warp.png", Tag::eOtherTag, _NowScene);

	//体力UI生成
	for (int i = 0; i < 3; i++)
	{
		mHeartUI = new HeartUI(Vector2(i * 100.0f, 50.0f), Tag::eOtherTag, Scene::eStage02, mPlayer);
	}

	mClearFlag = false;
	mNextSceneCount = 0;
}

/*
@fn	デストラクタ
*/
SecondStageScene::~SecondStageScene()
{
	GAME_OBJECT_MANAGER->RemoveSceneGameObject(Scene::eStage02);
	delete mSprite;
	delete mMapCreate;
	delete mGoalLineRoot;
}

/*
@fn    現在のシーン時に毎フレーム更新処理をする
@param _KeyState 各入力機器の入力状態
*/
SceneBase* SecondStageScene::UpdateScene(const InputState& _KeyState)
{
	//次のシーンに遷移するタイミング
	const int NextSceneTiming = 80;

	if (mPlayer->GetClearFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= NextSceneTiming)
		{
			return new GameClearScene(Scene::eGameClear);
		}
	}

	if (mPlayer->GetDeathFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= NextSceneTiming)
		{
			mTransitionFlag = true;
			return new ContinueScene(Scene::eContinue, Scene::eStage02, mTransitionFlag);
		}
	}

	return this;
}