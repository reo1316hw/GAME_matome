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