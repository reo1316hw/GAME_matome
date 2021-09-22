/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_NowScene ���݂̃V�[��
*/
Stage02Scene::Stage02Scene(const Scene& _NowScene)
	: mTransitionFlag(false)

{
	//����
	const Vector3 AmbientLight = Vector3(0.4f, 0.4f, 0.4f);
	//���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(AmbientLight);
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(0.0f, 1.0f, 0.0f);
	dir.m_diffuseColor = Vector3(0.5f, 0.6f, 0.8f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_NowScene);

	mGoalLine = new GoalLine(Vector3(800, 150, -2200), Vector3::sZERO, Tag::eOtherTag, Scene::eStage02);

	for (int i = 0; i < 3; i++)
	{
		if (i <= 1)
		{
			mCheckPointBoard = new CheckpointBoard(Vector3(800.0f, 500.0f,( -83100.0f + i * 22000.0f)), Vector3::sZERO, "Assets/checkpoint_stage02.png", Tag::eCheckpointTag, Scene::eStage02);
		}
		else
		{
			mCheckPointBoard = new CheckpointBoard(Vector3(800.0f, 500.0f, -29100.0f), Vector3::sZERO, "Assets/checkpoint_stage02.png", Tag::eCheckpointTag, Scene::eStage02);
		}
	}

	mSprite = new Sprite("Assets/stage04.png");

	mMapCreate = new MapCreate();
	mPlayer = mMapCreate->OpenStage02File();

	for (int i = 0; i < 3; i++)
	{
		mHeartUI = new HeartUI(Vector2(i * 100.0f, 50.0f), Tag::eOtherTag, Scene::eStage02, mPlayer);
	}

	mClearFlag = false;
	mNextSceneCount = 0;
}

/*
@fn	�f�X�g���N�^
*/
Stage02Scene::~Stage02Scene()
{
	GAME_OBJECT_MANAGER->RemoveSceneGameObject(Scene::eStage02);
	delete mSprite;
	delete mMapCreate;
}

/*
@fn    ���݂̃V�[�����ɖ��t���[���X�V����������
@param _KeyState �e���͋@��̓��͏��
*/
SceneBase* Stage02Scene::UpdateScene(const InputState& _KeyState)
{
	//���̃V�[���ɑJ�ڂ���^�C�~���O
	const int NextSceneTiming = 80;

	if (mPlayer->GetClearFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= NextSceneTiming)
		{
			return new GameClear(Scene::eGameClear);
		}
	}

	if (mPlayer->GetDeathFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= NextSceneTiming)
		{
			mTransitionFlag = true;
			return new ContinueScene(Scene::eContinue, Scene::eStage02, mTransitionFlag);
		}
	}

	return this;
}