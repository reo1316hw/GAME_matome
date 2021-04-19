/*
@brief	インクルード
*/
#include "TutorialScene.h"
#include "Stage01Scene.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "GameClear.h"
#include "GameOver.h"
#include "ContinueScene.h"
#include "EffectManager.h"
#include "Sprite.h"
#include "VerticalMoveGroundExplanationBoard.h"
#include "OperationExplanationBoard.h"
#include "GoalLine.h"
#include "MapCreate.h"
#include "HeartUI.h"

bool	TutorialScene::mSendContinueTutorialFlag = false;

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
TutorialScene::TutorialScene(const Scene& _nowScene)
{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(0.0f, 1.0f, 0.0f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.m_diffuseColor = Vector3(0.5f, 0.6f, 0.8f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_nowScene);

	mOperationExplanationBoard = new OperationExplanationBoard(Vector3(0, 200, -96000), Vector3::Zero, Tag::Other, Scene::tutorial);
	mVerticalMoveGroundExplanationBoard = new VerticalMoveGroundExplanationBoard(Vector3(0, 200,-92000), Vector3::Zero, Tag::Other, Scene::tutorial);
	mGoalLine = new GoalLine(Vector3(800, 150, -75800), Vector3::Zero, Tag::Other, Scene::tutorial);

	mSprite = new Sprite("Assets/forest.png");

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
		mMapCreate->CreateRightOneBlock();
		mMapCreate->CreateLeftOneBlock();
		mMapCreate->CreateGoal();
	}

	for (int i = 0; i < 3; i++)
	{
		mHeartUI = new HeartUI(Vector2(i * 100.0f, 50.0f), Tag::Other, Scene::tutorial);
	}

	mSendContinueTutorialFlag = false;
}

/*
@fn	デストラクタ
*/
TutorialScene::~TutorialScene()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(tutorial);
	delete mSprite;
	delete mMapCreate;
}

/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* TutorialScene::update()
{
	if (mPlayer->GetClearFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= 80)
		{
			mPlayer->SetClearFlag(false);

			/*return new GameClear(gameClear);*/
			return new Stage01Scene(stage01);
		}
	}

	if (mPlayer->GetDeathFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= 80)
		{
			mPlayer->SetDeathFlag(false);
			mContinueTutorialFlag = true;
			mSendContinueTutorialFlag = mContinueTutorialFlag;
			
			return new ContinueScene(Continue);
		}
	}

	return this;
}