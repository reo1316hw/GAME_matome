/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_NowScene 現在のシーン
*/
TitleScene::TitleScene(const Scene& _NowScene)
{
	//環境光
	const Vector3 AmbientLight = Vector3(0.4f, 0.4f, 0.4f);
	//ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(AmbientLight);
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(1.0f, 0.7f, -0.7f);
	dir.m_diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_NowScene);

	mSprite = new Sprite("Assets/title.png");

	mNextSceneCount = 0;
}

/*
@fn	デストラクタ
*/
TitleScene::~TitleScene()
{
	delete mSprite;
}

/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* TitleScene::UpdateScene(const InputState& _State)
{
	if (_State.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_START) == ButtonState::eReleased ||
		_State.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::eReleased)
	{
		//return new TutorialScene(Scene::eTutorial);
		//return new Stage01Scene(Scene::eStage01);
		return new Stage02Scene(Scene::eStage02);
	}

	return this;
}