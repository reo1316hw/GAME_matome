#include "Stage02Scene.h"
#include "GameClear.h"
#include "GameOver.h"
#include "ContinueScene.h"
#include "Stage01Scene.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "HeartUI.h"
#include "Sprite.h"
#include "Goal.h"
#include "MapCreate.h"

bool	Stage02Scene::mSendContinueStage02Flag = false;

Stage02Scene::Stage02Scene(const Scene& _nowScene)
{
	// ƒ‰ƒCƒg‚ðÝ’è(Ý’è‚µ‚È‚¢‚Æ‰½‚à‰f‚ç‚È‚¢)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(0.0f, 1.0f, 0.0f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.m_diffuseColor = Vector3(0.5f, 0.6f, 0.8f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_nowScene);

	mGoalLine = new Goal(Vector3(800, 150, -2200), Vector3::Zero, Tag::Other, Scene::stage02);

	mSprite = new Sprite("Assets/stage04.png");

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
		mMapCreate->CreateUpBlock();
		mMapCreate->CreateUpBlock_02();
		mMapCreate->CreateVerticalBlock();
		mMapCreate->CreateAerialBlock();
		mMapCreate->CreateRightBlock();
		mMapCreate->CreateLeftBlock();
		mMapCreate->CreateRightOneBlock();
		mMapCreate->CreateRightOneBlock_02();
		mMapCreate->CreateLeftOneBlock();
		mMapCreate->CreateLeftOneBlock_02();
		mMapCreate->CreateDownBlock();
		mMapCreate->CreateGoal();
		mMapCreate->CreateRespawn01();
		mMapCreate->CreateRespawn02();
		mMapCreate->CreateRespawn03();
	}

	for (int i = 0; i < 3; i++)
	{
		mHeartUI = new HeartUI(Vector2(i * 100.0f, 50.0f), Scene::stage02, Tag::Other);
	}

	mClearFlag = false;

	mContinueStage02Flag = false;
	mNextSceneCount = 0;
}

Stage02Scene::~Stage02Scene()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(stage02);
	delete mSprite;
	delete mMapCreate;
}

SceneBase* Stage02Scene::update()
{
	if (mPlayer->GetClearFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= 80)
		{
			mPlayer->SetClearFlag(false);

			return new GameClear(gameClear);
		}
	}

	if (mPlayer->GetDeathFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= 80)
		{
			mPlayer->SetDeathFlag(false);
			mContinueStage02Flag = true;
			mSendContinueStage02Flag = mContinueStage02Flag;

			return new ContinueScene(Continue);
		}
	}

	return this;
}