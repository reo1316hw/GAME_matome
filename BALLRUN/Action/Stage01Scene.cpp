#include "Stage01Scene.h"
#include "Stage02Scene.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "GameClear.h"
#include "GameOver.h"
#include "ContinueScene.h"
#include "HeartUI.h"
#include "Sprite.h"

bool	Stage01Scene::sendContinueStage01Flag = false;

Stage01Scene::Stage01Scene(const Scene& _scene)
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

	goal = new Goal(Vector3(800, 150, -9000), Vector3::Zero, Tag::Other, Scene::stage01);

	sprite = new Sprite("Assets/sea.png");

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
		mapCreate->CreateGoal();
		mapCreate->CreateRespawn01();
		mapCreate->CreateRespawn02();
		mapCreate->CreateRespawn03();
	}

	for (int i = 0; i < 3; i++)
	{
		heartUI = new HeartUI(Vector2(i * 100.0f, 50.0f), Scene::stage01, Tag::Other);
	}

	continueStage01Flag = false;
	count = 0;
}

Stage01Scene::~Stage01Scene()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(stage01);
	/*delete heartUI;*/
	delete sprite;
	delete mapCreate;
	/*GAME_OBJECT_MANAGER->RemoveGameObject();*/
}

SceneBase* Stage01Scene::update()
{
	if (player->GetClearFlag())
	{
		count++;

		if (count >= 80)
		{
			player->SetClearFlag(false);

			/*return new GameClear(gameClear);*/
			return new Stage02Scene(stage02);
		}
	}

	if (player->GetDeathFlag())
	{
		count++;

		if (count >= 80)
		{
			player->SetDeathFlag(false);
			continueStage01Flag = true;
			sendContinueStage01Flag = continueStage01Flag;

			return new ContinueScene(Continue);
		}
	}

	return this;
}

void Stage01Scene::draw()
{

	/*sprite->Draw(shader);*/

	RENDERER->Draw();
}