/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_NowScene 現在のシーン
*/
ContinueScene::ContinueScene(const Scene& _NowScene, const Scene& _PreScene, const bool _TransitionSceneFlag)
	: mTutorialTransitionFlag(false)
	, mStage01TransitionFlag(false)
	, mStage02TransitionFlag(false)
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

	mSprite = new Sprite("Assets/BackGround/Continue.png");

	switch (_PreScene)
	{
	case Scene::eTutorial:

		mTutorialTransitionFlag = _TransitionSceneFlag;
		break;
	case Scene::eStage01:

		mStage01TransitionFlag = _TransitionSceneFlag;
		break;
	case Scene::eStage02:

		mStage02TransitionFlag = _TransitionSceneFlag;
		break;
	}
}

/*
@fn	デストラクタ
*/
ContinueScene::~ContinueScene()
{
	delete mSprite;
}

/*
@fn    現在のシーン時に毎フレーム更新処理をする
@param _KeyState 各入力機器の入力状態
*/
SceneBase* ContinueScene::UpdateScene(const InputState& _KeyState)
{
	if (mTutorialTransitionFlag)
	{
		if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == ButtonState::eReleased ||
			_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_Q) == ButtonState::eReleased)
		{
			mTutorialTransitionFlag = false;
			return new TutorialStageScene(Scene::eTutorial);
		}
	}

	if (mStage01TransitionFlag)
	{
		if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == ButtonState::eReleased ||
			_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_Q) == ButtonState::eReleased)
		{
			mStage01TransitionFlag = false;
			return new FirstStageScene(Scene::eStage01);
		}
	}

	if (mStage02TransitionFlag)
	{
		if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == ButtonState::eReleased ||
			_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_Q) == ButtonState::eReleased)
		{
			mStage02TransitionFlag = false;
			return new SecondStageScene(Scene::eStage02);
		}
	}

	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == ButtonState::eReleased ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_E) == ButtonState::eReleased)
	{
		return new GameOverScene(Scene::eGameOver);
	}

	return this;
}
