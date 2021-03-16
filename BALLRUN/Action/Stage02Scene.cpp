#include "Stage02Scene.h"
#include "GameClear.h"
#include "GameOver.h"
#include "ContinueScene.h"
#include "Stage01Scene.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "HeartUI.h"
#include "Sprite.h"

bool	Stage02Scene::sendContinueStage02Flag = false;

Stage02Scene::Stage02Scene(const Scene& _scene)
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

	goal = new Goal(Vector3(800, 150, -2200), Vector3::Zero, Tag::Other, Scene::stage02);

	sprite = new Sprite("Assets/stage04.png");

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
		mapCreate->CreateUpBlock_02();
		mapCreate->CreateVerticalBlock();
		mapCreate->CreateAerialBlock();
		mapCreate->CreateRightBlock();
		mapCreate->CreateLeftBlock();
		mapCreate->CreateRightOneBlock();
		mapCreate->CreateRightOneBlock_02();
		mapCreate->CreateLeftOneBlock();
		mapCreate->CreateLeftOneBlock_02();
		mapCreate->CreateDownBlock();
		mapCreate->CreateGoal();
		mapCreate->CreateRespawn01();
		mapCreate->CreateRespawn02();
		mapCreate->CreateRespawn03();
	}

	for (int i = 0; i < 3; i++)
	{
		heartUI = new HeartUI(Vector2(i * 100.0f, 50.0f), Scene::stage02, Tag::Other);
	}

	clearFlag = false;

	continueStage02Flag = false;
	count = 0;
}

Stage02Scene::~Stage02Scene()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(stage02);
	/*delete heartUI;*/
	delete sprite;
	delete mapCreate;
	/*GAME_OBJECT_MANAGER->RemoveAllUsedGameObject();*/
}

SceneBase* Stage02Scene::update()
{
	if (player->GetClearFlag())
	{
		count++;

		if (count >= 80)
		{
			player->SetClearFlag(false);

			return new GameClear(gameClear);
		}
	}

	if (player->GetDeathFlag())
	{
		count++;

		if (count >= 80)
		{
			player->SetDeathFlag(false);
			continueStage02Flag = true;
			sendContinueStage02Flag = continueStage02Flag;

			return new ContinueScene(Continue);
		}
	}

	/*count++;*/

	if (count >= 100)
	{
		/*MapCreate* mapCreate = new MapCreate();
		mapCreate->ClearFile();*/

		return new Stage01Scene(stage01);
	}

	return this;
}

void Stage02Scene::draw()
{
	/*sprite->Draw(shader);*/

	RENDERER->Draw();
}