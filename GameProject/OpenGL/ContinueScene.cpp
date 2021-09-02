/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
ContinueScene::ContinueScene(const Scene& _nowScene)
{
	// ���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(1.0f, 0.7f, -0.7f);
	dir.m_diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_nowScene);

	mSprite = new Sprite("Assets/continue.png");
}

/*
@fn	�f�X�g���N�^
*/
ContinueScene::~ContinueScene()
{
	delete mSprite;
}

/*
@fn	���݂̃V�[�����ɖ��t���[���X�V����������
*/
SceneBase* ContinueScene::update(const InputState& _state)
{
	if (mTutorial->GetContinueTutorialFlag())
	{
		if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
			_state.m_keyboard.GetKeyState(SDL_SCANCODE_Q) == Released)
		{
			mTutorial->SetContinueTutorialFlag(false);
			return new TutorialScene(SceneBase::tutorial);
		}

		/*if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
			_state.m_keyboard.GetKeyValue(SDL_SCANCODE_Q) == 1)
		{
			mTutorial->SetContinueTutorialFlag(false);
			return new TutorialScene(SceneBase::tutorial);
		}*/
	}

	if (mStage01->GetContinueStage01Flag())
	{
		if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
			_state.m_keyboard.GetKeyState(SDL_SCANCODE_Q) == Released)
		{
			mStage01->SetContinueStage01Flag(false);
			return new Stage01Scene(SceneBase::stage01);
		}

		/*if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
			_state.m_keyboard.GetKeyValue(SDL_SCANCODE_Q) == 1)
		{
			mStage01->SetContinueStage01Flag(false);
			return new Stage01Scene(SceneBase::stage01);
		}*/
	}

	if (mStage02->GetContinueStage02Flag())
	{
		if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
			_state.m_keyboard.GetKeyState(SDL_SCANCODE_Q) == Released)
		{
			mStage02->SetContinueStage02Flag(false);
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
