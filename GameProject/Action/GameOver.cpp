#include "GameOver.h"
#include "TitleScene.h"
#include "Renderer.h"
#include "Sprite.h"
#include "InputSystem.h"

GameOver::GameOver(const Scene& _scene)
{
	// ƒ‰ƒCƒg‚ðÝ’è(Ý’è‚µ‚È‚¢‚Æ‰½‚à‰f‚ç‚È‚¢)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(1.0f, 0.7f, -0.7f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.m_diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_scene);

	mInputSystem = new InputSystem();
	mInputSystem->Initialize();

	mSprite = new Sprite("Assets/GameOver02.png");

	mNextSceneCount = 0;
}

GameOver::~GameOver()
{
	delete mSprite;
}

SceneBase* GameOver::update()
{
	mNextSceneCount++;
	if (mNextSceneCount >= 160)
	{
		return new TitleScene(title);
	}

	/*inputSystem->PrepareForUpdate();
	inputSystem->Update();

	const InputState& sceneState = inputSystem->GetState();

	if (sceneState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
		sceneState.Keyboard.GetKeyValue(SDL_SCANCODE_E) == 1)
	{
		return new TitleScene(title);
	}*/

	/*if (sceneState.Keyboard.GetKeyState(SDL_SCANCODE_E) == Pressed)
	{
		return new TitleScene(title);
	}*/

	return this;
}
