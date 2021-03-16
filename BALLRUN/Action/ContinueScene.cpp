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
	// ƒ‰ƒCƒg‚ðÝ’è(Ý’è‚µ‚È‚¢‚Æ‰½‚à‰f‚ç‚È‚¢)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(1.0f, 0.7f, -0.7f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_scene);

	inputSystem = new InputSystem();
	inputSystem->Initialize();

	sprite = new Sprite("Assets/continue.png");

	count = 0;
}

ContinueScene::~ContinueScene()
{
	delete sprite;
}

SceneBase* ContinueScene::update()
{
	/*count++;
	if (count >= 160)
	{
		return new GameOver(gameOver);
	}*/

	inputSystem->PrepareForUpdate();
	inputSystem->Update();

	const InputState& sceneState = inputSystem->GetState();

	if (tutorial->GetContinueTutorialFlag())
	{
		/*if (sceneState.Keyboard.GetKeyState(SDL_SCANCODE_Q) == Pressed)
		{
			return new Tutorial(SceneBase::tutorial);
		}*/

		if (sceneState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
			sceneState.Keyboard.GetKeyValue(SDL_SCANCODE_Q) == 1)
		{
			tutorial->SetContinueTutorialFlag(false);
			return new Tutorial(SceneBase::tutorial);
		}
	}

	if (stage01->GetContinueStage01Flag())
	{
		/*if (sceneState.Keyboard.GetKeyState(SDL_SCANCODE_Q) == Pressed)
		{
			tutorial->SetContinueTutorialFlag(false);
			return new Tutorial(SceneBase::tutorial);
		}*/

		if (sceneState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
			sceneState.Keyboard.GetKeyValue(SDL_SCANCODE_Q) == 1)
		{
			stage01->SetContinueStage01Flag(false);
			return new Stage01Scene(SceneBase::stage01);
		}
	}

	if (stage02->GetContinueStage02Flag())
	{
		/*if (sceneState.Keyboard.GetKeyState(SDL_SCANCODE_Q) == Pressed)
		{
			tutorial->SetContinueTutorialFlag(false);
			return new Tutorial(SceneBase::tutorial);
		}*/

		if (sceneState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
			sceneState.Keyboard.GetKeyValue(SDL_SCANCODE_Q) == 1)
		{
			stage02->SetContinueStage02Flag(false);
			return new Stage02Scene(SceneBase::stage02);
		}
	}

	if (sceneState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_B) == 1 ||
		sceneState.Keyboard.GetKeyValue(SDL_SCANCODE_E) == 1)
	{
		return new GameOver(SceneBase::gameOver);

	}

	return this;
}

void ContinueScene::draw()
{
	RENDERER->Draw();
}
