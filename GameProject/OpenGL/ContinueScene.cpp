/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_NowScene ���݂̃V�[��
*/
ContinueScene::ContinueScene(const Scene& _NowScene, const Scene& _PreScene, const bool _TransitionSceneFlag)
	: mTutorialTransitionFlag(false)
	, mStage01TransitionFlag(false)
	, mStage02TransitionFlag(false)
{
	//����
	const Vector3 AmbientLight = Vector3(0.4f, 0.4f, 0.4f);
	//���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
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
@fn	�f�X�g���N�^
*/
ContinueScene::~ContinueScene()
{
	delete mSprite;
}

/*
@fn    ���݂̃V�[�����ɖ��t���[���X�V����������
@param _KeyState �e���͋@��̓��͏��
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
