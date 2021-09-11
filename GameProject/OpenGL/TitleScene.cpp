/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
TitleScene::TitleScene(const Scene& _nowScene)
{
	// ���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(1.0f, 0.7f, -0.7f);
	dir.m_diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_nowScene);

	mSprite = new Sprite("Assets/title.png");

	mNextSceneCount = 0;
}

/*
@fn	�f�X�g���N�^
*/
TitleScene::~TitleScene()
{
	delete mSprite;
}

/*
@fn	���݂̃V�[�����ɖ��t���[���X�V����������
*/
SceneBase* TitleScene::update(const InputState& _state)
{
	if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_START) == Released ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Released)
	{
		//return new TutorialScene(tutorial);
		return new Stage01Scene(stage01);
		//return new Stage02Scene(stage02);
	}

	//if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
	//	_state.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE) == 1)
	//{
	//	return new TutorialScene(tutorial);
	//	//return new Stage01Scene(stage01);
	//	//return new Stage02Scene(stage02);
	//}

	return this;
}