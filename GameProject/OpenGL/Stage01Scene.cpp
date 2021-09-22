/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_NowScene 現在のシーン
*/
Stage01Scene::Stage01Scene(const Scene& _NowScene)
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

	mGoalLine = new GoalLine(Vector3(800, 150, -9000), Vector3::sZERO, Tag::eOtherTag, Scene::eStage01);

	for (int i = 0; i < 3; i++)
	{
		if (i <= 1)
		{
  			mCheckPointBoard = new CheckpointBoard(Vector3(800.0f, 300.0f, (-81100.0f + i * 25000.0f)), Vector3::sZERO, "Assets/checkpoint_stage01.png", Tag::eCheckpointTag, Scene::eStage01);
		}
		else
		{
			mCheckPointBoard = new CheckpointBoard(Vector3(800.0f, 300.0f, -39700.0f), Vector3::sZERO, "Assets/checkpoint_stage01.png", Tag::eCheckpointTag, Scene::eStage01);
		}
	}

	mSprite = new Sprite("Assets/sea.png");

	mMapCreate = new MapCreate();
	mPlayer = mMapCreate->OpenStage01File();

	for (int i = 0; i < 3; i++)
	{
		mHeartUI = new HeartUI(Vector2(i * 100.0f, 50.0f), Tag::eOtherTag, Scene::eStage01, mPlayer);
	}

	mNextSceneCount = 0;
}

/*
@fn	デストラクタ
*/
Stage01Scene::~Stage01Scene()
{
	GAME_OBJECT_MANAGER->RemoveSceneGameObject(Scene::eStage01);
	delete mSprite;
	delete mMapCreate;
}

/*
@fn    現在のシーン時に毎フレーム更新処理をする
@param _KeyState 各入力機器の入力状態
*/
SceneBase* Stage01Scene::UpdateScene(const InputState& _KeyState)
{
	//次のシーンに遷移するタイミング
	const int NextSceneTiming = 80;

	if (mPlayer->GetClearFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= NextSceneTiming)
		{
			return new Stage02Scene(Scene::eStage02);
		}
	}

	if (mPlayer->GetDeathFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= NextSceneTiming)
		{
			mTransitionFlag = true;
			return new ContinueScene(Scene::eContinue, Scene::eStage01, mTransitionFlag);
		}
	}

	return this;
}