/*
@brief	インクルード
*/
#include "Stage01Scene.h"
#include "Stage02Scene.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "GameClear.h"
#include "GameOver.h"
#include "ContinueScene.h"
#include "HeartUI.h"
#include "Sprite.h"
#include "GoalLine.h"
#include "CheckpointBoard.h"
#include "MapCreate.h"

bool	Stage01Scene::mSendContinueStage01Flag = false;

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
Stage01Scene::Stage01Scene(const Scene& _nowScene)
{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(0.0f, 1.0f, 0.0f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.m_diffuseColor = Vector3(0.5f, 0.6f, 0.8f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_nowScene);

	mGoalLine = new GoalLine(Vector3(800, 150, -9000), Vector3::Zero, Tag::Other, Scene::stage01);

	for (int i = 0; i < 3; i++)
	{
		if (i <= 1)
		{
  			mCheckPointBoard = new CheckpointBoard(Vector3(800.0f, 300.0f, (-79500.0f + i * 24000.0f)), Vector3::Zero, "Assets/checkpoint_stage01.png", Tag::checkpoint, Scene::stage01);

		}
		else
		{
			mCheckPointBoard = new CheckpointBoard(Vector3(800.0f, 300.0f, -36800), Vector3::Zero, "Assets/checkpoint_stage01.png", Tag::checkpoint, Scene::stage01);
		}
	}

	mSprite = new Sprite("Assets/sea.png");

	mMapCreate = new MapCreate();
	if (!mMapCreate->OpenFile())
	{
		mMapCreate->CreateGround();
		mMapCreate->CreateGlass();
		mMapCreate->CreateBlock();
		mMapCreate->CreateVerticalMoveGround();
		mMapCreate->CreateJump();
		mMapCreate->CreateLateralMoveGround();
		mMapCreate->CreatePlayer();
		mMapCreate->CreateGoal();
		mMapCreate->CreateRespawn01();
		mMapCreate->CreateRespawn02();
		mMapCreate->CreateRespawn03();
	}

	for (int i = 0; i < 3; i++)
	{
		mHeartUI = new HeartUI(Vector2(i * 100.0f, 50.0f), Tag::Other, Scene::stage01);
	}

	mContinueStage01Flag = false;
	mNextSceneCount = 0;
}

/*
@fn	デストラクタ
*/
Stage01Scene::~Stage01Scene()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(stage01);
	delete mSprite;
	delete mMapCreate;
	/*GAME_OBJECT_MANAGER->RemoveGameObject();*/
}

/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* Stage01Scene::update()
{
	if (mPlayer->GetClearFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= 80)
		{
			mPlayer->SetClearFlag(false);

			/*return new GameClear(gameClear);*/
			return new Stage02Scene(stage02);
		}
	}

	if (mPlayer->GetDeathFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= 80)
		{
			mPlayer->SetDeathFlag(false);
			mContinueStage01Flag = true;
			mSendContinueStage01Flag = mContinueStage01Flag;

			return new ContinueScene(Continue);
		}
	}

	return this;
}