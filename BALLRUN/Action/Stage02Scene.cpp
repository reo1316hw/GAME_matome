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
	// ���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(0.0f, 1.0f, 0.0f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.diffuseColor = Vector3(0.5f, 0.6f, 0.8f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_scene);
	/*GameObject::CreateMainCamera();*/
	/*
	�e�X�g���f���̐����@����͂��̃I�u�W�F�N�g�̌p�����������ŃI�u�W�F�N�g�S�̂��Ǘ����Ă���N���X�ɒǉ����ꂻ�̃N���X�ōs����
	�@TestObject�����������
	�A���N���X����GameObjectManager���̃R���e�i�ɒǉ������
	�BGameObjectManager���������鎞�ɑS�ẴQ�[���I�u�W�F�N�g����������
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