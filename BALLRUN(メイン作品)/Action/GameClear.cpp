#include "GameClear.h"
#include "TitleScene.h"
#include "Stage01Scene.h"
#include "Renderer.h"
#include "Sprite.h"
#include "InputSystem.h"

GameClear::GameClear(const Scene& _scene)
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

	sprite = new Sprite("Assets/GameClear.png");

	count = 0;
}

GameClear::~GameClear()
{
	delete sprite;
}

SceneBase* GameClear::update()
{
	count++;
	if (count >= 160)
	{
		return new TitleScene(title);
	}

	//const InputState& sceneState = inputSystem->GetState();

	//if (sceneState.Keyboard.GetKeyState(SDL_SCANCODE_E) == Pressed)
	//{
	//	return new TitleScene(title);
	//}

	return this;
}

void GameClear::draw()
{
	RENDERER->Draw();
}
