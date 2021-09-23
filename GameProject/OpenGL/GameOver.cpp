/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_NowScene ���݂̃V�[��
*/
GameOver::GameOver(const Scene& _NowScene)
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

	mSprite = new Sprite("Assets/GameOver02.png");

	mNextSceneCount = 0;
}

/*
@fn	�f�X�g���N�^
*/
GameOver::~GameOver()
{
	delete mSprite;
}

/*
@fn    ���݂̃V�[�����ɖ��t���[���X�V����������
@param _KeyState �e���͋@��̓��͏��
*/
SceneBase* GameOver::UpdateScene(const InputState& _KeyState)
{
	//���̃V�[���ɑJ�ڂ���^�C�~���O
	const int NextSceneTiming = 160;

	mNextSceneCount++;
	if (mNextSceneCount >= NextSceneTiming)
	{
		return new TitleScene(Scene::eTitle);
	}

	return this;
}
