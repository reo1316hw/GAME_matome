#include "Stage01Scene.h"
#include "Stage02Scene.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "GameClear.h"
#include "GameOver.h"
#include "ContinueScene.h"
#include "HeartUI.h"
#include "Sprite.h"
#include "Goal.h"
#include "MapCreate.h"

bool	Stage01Scene::mSendContinueStage01Flag = false;

Stage01Scene::Stage01Scene(const Scene& _nowScene)
{
	// ƒ‰ƒCƒg‚ðÝ’è(Ý’è‚µ‚È‚¢‚Æ‰½‚à‰f‚ç‚È‚¢)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(0.0f, 1.0f, 0.0f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.m_diffuseColor = Vector3(0.5f, 0.6f, 0.8f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_nowScene);

	mGoalLine = new Goal(Vector3(800, 150, -9000), Vector3::Zero, Tag::Other, Scene::stage01);

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
		mHeartUI = new HeartUI(Vector2(i * 100.0f, 50.0f), Scene::stage01, Tag::Other);
	}

	mContinueStage01Flag = false;
	mNextSceneCount = 0;
}

Stage01Scene::~Stage01Scene()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(stage01);
	delete mSprite;
	delete mMapCreate;
	/*GAME_OBJECT_MANAGER->RemoveGameObject();*/
}

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