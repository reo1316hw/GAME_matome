/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
ContinueScene::ContinueScene(const Scene& _nowScene, const Scene& _preScene, const bool _transitionSceneFlag)
	: mTutorialTransitionFlag(false)
	, mStage01TransitionFlag(false)
	, mStage02TransitionFlag(false)
{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(1.0f, 0.7f, -0.7f);
	dir.m_diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_nowScene);

	mSprite = new Sprite("Assets/continue.png");

	switch (_preScene)
	{
	case tutorial:

		mTutorialTransitionFlag = _transitionSceneFlag;
		break;
	case stage01:

		mStage01TransitionFlag = _transitionSceneFlag;
		break;
	case stage02:

		mStage02TransitionFlag = _transitionSceneFlag;
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
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* ContinueScene::update(const InputState& _state)
{
	if (mTutorialTransitionFlag)
	{
		if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
			_state.m_keyboard.GetKeyState(SDL_SCANCODE_Q) == Released)
		{
			mTutorialTransitionFlag = false;
			return new TutorialScene(SceneBase::tutorial);
		}

		/*if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
			_state.m_keyboard.GetKeyValue(SDL_SCANCODE_Q) == 1)
		{
			mTutorial->SetContinueTutorialFlag(false);
			return new TutorialScene(SceneBase::tutorial);
		}*/
	}

	if (mStage01TransitionFlag)
	{
		if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
			_state.m_keyboard.GetKeyState(SDL_SCANCODE_Q) == Released)
		{
			mStage01TransitionFlag = false;
			return new Stage01Scene(SceneBase::stage01);
		}

		/*if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
			_state.m_keyboard.GetKeyValue(SDL_SCANCODE_Q) == 1)
		{
			mStage01->SetContinueStage01Flag(false);
			return new Stage01Scene(SceneBase::stage01);
		}*/
	}

	if (mStage02TransitionFlag)
	{
		if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
			_state.m_keyboard.GetKeyState(SDL_SCANCODE_Q) == Released)
		{
			mStage02TransitionFlag = false;
			return new Stage02Scene(SceneBase::stage02);
		}

		/*if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
			_state.m_keyboard.GetKeyValue(SDL_SCANCODE_Q) == 1)
		{
			mStage02->SetContinueStage02Flag(false);
			return new Stage02Scene(SceneBase::stage02);
		}*/
	}

	if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Released ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_E) == Released)
	{
		return new GameOver(SceneBase::gameOver);
	}

	return this;
}
