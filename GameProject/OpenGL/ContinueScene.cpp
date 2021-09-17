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

	mSprite = new Sprite("Assets/continue.png");

	switch (_PreScene)
	{
	case tutorial:

		mTutorialTransitionFlag = _TransitionSceneFlag;
		break;
	case stage01:

		mStage01TransitionFlag = _TransitionSceneFlag;
		break;
	case stage02:

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
@fn	���݂̃V�[�����ɖ��t���[���X�V����������
*/
SceneBase* ContinueScene::UpdateScene(const InputState& _State)
{
	if (mTutorialTransitionFlag)
	{
		if (_State.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
			_State.m_keyboard.GetKeyState(SDL_SCANCODE_Q) == Released)
		{
			mTutorialTransitionFlag = false;
			return new TutorialScene(SceneBase::tutorial);
		}
	}

	if (mStage01TransitionFlag)
	{
		if (_State.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
			_State.m_keyboard.GetKeyState(SDL_SCANCODE_Q) == Released)
		{
			mStage01TransitionFlag = false;
			return new Stage01Scene(SceneBase::stage01);
		}
	}

	if (mStage02TransitionFlag)
	{
		if (_State.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
			_State.m_keyboard.GetKeyState(SDL_SCANCODE_Q) == Released)
		{
			mStage02TransitionFlag = false;
			return new Stage02Scene(SceneBase::stage02);
		}
	}

	if (_State.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Released ||
		_State.m_keyboard.GetKeyState(SDL_SCANCODE_E) == Released)
	{
		return new GameOver(SceneBase::gameOver);
	}

	return this;
}
