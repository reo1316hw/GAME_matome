#include "Tutorial.h"
#include "Stage01Scene.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "GameClear.h"
#include "GameOver.h"
#include "ContinueScene.h"
#include "EffectManager.h"
#include "Sprite.h"

bool	Tutorial::sendContinueTutorialFlag = false;

Tutorial::Tutorial(const Scene& _scene)
{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(0.0f, 1.0f, 0.0f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.diffuseColor = Vector3(0.5f, 0.6f, 0.8f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_scene);
	/*GameObject::CreateMainCamera();*/

	/*
	テストモデルの生成　解放はこのオブジェクトの継承元が自動でオブジェクト全体を管理しているクラスに追加されそのクラスで行われる
	①TestObjectが生成される
	②基底クラス内でGameObjectManager内のコンテナに追加される
	③GameObjectManagerが解放される時に全てのゲームオブジェクトが解放される
	*/

	tutorialEffect = new TutorialEffect(Vector3(0, 200, -96000), Vector3::Zero, Tag::Other, Scene::tutorial);
	tutorialVertEffect = new TutorialVerticalEffect(Vector3(0, 200,-92000), Vector3::Zero, Tag::Other, Scene::tutorial);
	goal = new Goal(Vector3(800, 150, -75800), Vector3::Zero, Tag::Other, Scene::tutorial);

	sprite = new Sprite("Assets/forest.png");

	mapCreate = new MapCreate();
	if (!mapCreate->OpenFile())
	{
		mapCreate->CreateGround();
		mapCreate->CreateGlass();
		mapCreate->CreateBlock();
		mapCreate->CreateVerticalMoveGround();
		mapCreate->CreateJump();
		mapCreate->CreateLateralMoveGround();
		mapCreate->CreatePlayer();
		mapCreate->CreateUpBlock();
		mapCreate->CreateRightOneBlock();
		mapCreate->CreateLeftOneBlock();
		mapCreate->CreateGoal();
	}

	for (int i = 0; i < 3; i++)
	{
		heartUI = new HeartUI(Vector2(i * 100.0f, 50.0f), Scene::tutorial, Tag::Other);
	}

	continueTutorialFlag = false;
	count = 0;
}

Tutorial::~Tutorial()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(tutorial);
	/*delete heartUI;*/
	delete sprite;
	delete mapCreate;
	/*GAME_OBJECT_MANAGER->RemoveGameObject();*/
}

SceneBase* Tutorial::update()
{
	if (player->GetClearFlag())
	{
		count++;

		if (count >= 80)
		{
			player->SetClearFlag(false);

			/*return new GameClear(gameClear);*/
			return new Stage01Scene(stage01);
		}
	}

	if (player->GetDeathFlag())
	{
		count++;

		if (count >= 80)
		{
			player->SetDeathFlag(false);
			continueTutorialFlag = true;
			sendContinueTutorialFlag = continueTutorialFlag;
			
			return new ContinueScene(Continue);
		}
	}

	return this;
}

void Tutorial::draw()
{

	RENDERER->Draw();

	/*for (int i = 0; i < 3; i++)
	{
		RENDERER->DrawTexture(uiTexture, Vector2((i + 1) * 60.0f, 50.0f));
	}*/
}