#include "ContinueScene.h"
#include "Tutorial.h"
#include "Stage01Scene.h"
#include "Stage02Scene.h"
#include "GameOver.h"
#include "TitleScene.h"
#include "Stage01Scene.h"
#include "Renderer.h"
#include "Sprite.h"
#include "InputSystem.h"

ContinueScene::ContinueScene(const Scene& _scene)
{
	// ���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(1.0f, 0.7f, -0.7f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.m_diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_scene);

	mInputSystem = new InputSystem();
	mInputSystem->Initialize();

	mSprite = new Sprite("Assets/continue.png");
}

ContinueScene::~ContinueScene()
{
	delete mSprite;
}

SceneBase* ContinueScene::update()
{
	mInputSystem->PrepareForUpdate();
	mInputSystem->Update();

	const InputState& sceneState = mInputSystem->GetState();

	if (mTutorial->GetContinueTutorialFlag())
	{
		/*if (sceneState.Keyboard.GetKeyState(SDL_SCANCODE_Q) == Pressed)
		{
			return new Tutorial(SceneBase::mTutorial);
		}*/

		if (sceneState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
			sceneState.m_keyboard.GetKeyValue(SDL_SCANCODE_Q) == 1)
		{
			mTutorial->SetContinueTutorialFlag(false);
			return new Tutorial(SceneBase::tutorial);
		}
	}

	if (mStage01->GetContinueStage01Flag())
	{
		/*if (sceneState.Keyboard.GetKeyState(SDL_SCANCODE_Q) == Pressed)
		{
			mTutorial->SetContinueTutorialFlag(false);
			return new Tutorial(SceneBase::mTutorial);
		}*/

		if (sceneState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
			sceneState.m_keyboard.GetKeyValue(SDL_SCANCODE_Q) == 1)
		{
			mStage01->SetContinueStage01Flag(false);
			return new Stage01Scene(SceneBase::stage01);
		}
	}

	if (mStage02->GetContinueStage02Flag())
	{
		/*if (sceneState.Keyboard.GetKeyState(SDL_SCANCODE_Q) == Pressed)
		{
			mTutorial->SetContinueTutorialFlag(false);
			return new Tutorial(SceneBase::mTutorial);
		}*/

		if (sceneState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
			sceneState.m_keyboard.GetKeyValue(SDL_SCANCODE_Q) == 1)
		{
			mStage02->SetContinueStage02Flag(false);
			return new Stage02Scene(SceneBase::stage02);
		}
	}

	if (sceneState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_B) == 1 ||
		sceneState.m_keyboard.GetKeyValue(SDL_SCANCODE_E) == 1)
	{
		return new GameOver(SceneBase::gameOver);
	}

	return this;
}