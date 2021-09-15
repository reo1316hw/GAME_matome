/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
Stage02Scene::Stage02Scene(const Scene& _nowScene)
	: mTransitionFlag(false)

{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(0.0f, 1.0f, 0.0f);
	dir.m_diffuseColor = Vector3(0.5f, 0.6f, 0.8f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_nowScene);

	mGoalLine = new GoalLine(Vector3(800, 150, -2200), Vector3::Zero, Tag::Other, Scene::stage02);

	for (int i = 0; i < 3; i++)
	{
		if (i <= 1)
		{
			mCheckPointBoard = new CheckpointBoard(Vector3(800.0f, 500.0f,( -83100.0f + i * 22000.0f)), Vector3::Zero, "Assets/checkpoint_stage02.png", Tag::checkpoint, Scene::stage02);
		}
		else
		{
			mCheckPointBoard = new CheckpointBoard(Vector3(800.0f, 500.0f, -29100.0f), Vector3::Zero, "Assets/checkpoint_stage02.png", Tag::checkpoint, Scene::stage02);
		}
	}

	mSprite = new Sprite("Assets/stage04.png");

	mMapCreate = new MapCreate();
	mPlayer = mMapCreate->OpenStage02File();

	for (int i = 0; i < 3; i++)
	{
		mHeartUI = new HeartUI(Vector2(i * 100.0f, 50.0f), Tag::Other, Scene::stage02, mPlayer);
	}

	mClearFlag = false;
	mNextSceneCount = 0;
}

/*
@fn	デストラクタ
*/
Stage02Scene::~Stage02Scene()
{
	GAME_OBJECT_MANAGER->RemoveSceneGameObject(stage02);
	delete mSprite;
	delete mMapCreate;
}

/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* Stage02Scene::update(const InputState& _state)
{
	if (mPlayer->GetClearFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= 80)
		{
			return new GameClear(gameClear);
		}
	}

	if (mPlayer->GetDeathFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= 80)
		{
			mTransitionFlag = true;
			return new ContinueScene(Continue, stage02, mTransitionFlag);
		}
	}

	return this;
}