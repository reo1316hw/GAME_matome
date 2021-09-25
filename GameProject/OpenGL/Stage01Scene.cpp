/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_NowScene ���݂̃V�[��
*/
Stage01Scene::Stage01Scene(const Scene& _NowScene)
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

	mSprite = new Sprite("Assets/sea.png");

	mMapCreate = new MapCreate();
	mPlayer = mMapCreate->OpenStage01File();

	//�e�S�[�����C���̍��㌴�_
	const Vector3 TopLeftOriginGoalLine = Vector3(300.0f, 200.0f, -9000.0f);
	//�e�S�[�����C���𐶐�
	mGoalLineRoot = new GoalLineRoot(TopLeftOriginGoalLine, _NowScene, mPlayer);

	//�`�F�b�N�|�C���g�{�[�h����
	for (int i = 0; i < 3; i++)
	{
		if (i <= 1)
		{
			mCheckPointBoard = new CheckpointBoard(Vector3(800.0f, 300.0f, (-81100.0f + i * 25000.0f)), Vector3::sZERO, "Assets/checkpoint_stage01.png", Tag::eCheckpointTag, _NowScene);
		}
		else
		{
			mCheckPointBoard = new CheckpointBoard(Vector3(800.0f, 300.0f, -39700.0f), Vector3::sZERO, "Assets/checkpoint_stage01.png", Tag::eCheckpointTag, _NowScene);
		}
	}

	//�S�[�����[�v����
	mGoalWarpBorard = new GoalWarpBorard(Vector3(800.0f, 350.0f, -7800.0f), Vector3::sZERO, "Assets/Warp.png", Tag::eOtherTag, _NowScene);

	//�̗�UI����
	for (int i = 0; i < 3; i++)
	{
		mHeartUI = new HeartUI(Vector2(i * 100.0f, 50.0f), Tag::eOtherTag, Scene::eStage01, mPlayer);
	}

	mNextSceneCount = 0;
}

/*
@fn	�f�X�g���N�^
*/
Stage01Scene::~Stage01Scene()
{
	GAME_OBJECT_MANAGER->RemoveSceneGameObject(Scene::eStage01);
	delete mSprite;
	delete mMapCreate;
	delete mGoalLineRoot;
}

/*
@fn    ���݂̃V�[�����ɖ��t���[���X�V����������
@param _KeyState �e���͋@��̓��͏��
*/
SceneBase* Stage01Scene::UpdateScene(const InputState& _KeyState)
{
	//���̃V�[���ɑJ�ڂ���^�C�~���O
	const int NextSceneTiming = 80;

	if (mPlayer->GetClearFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= NextSceneTiming)
		{
			return new Stage02Scene(Scene::eStage02);
		}
	}

	if (mPlayer->GetDeathFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= NextSceneTiming)
		{
			mTransitionFlag = true;
			return new ContinueScene(Scene::eContinue, Scene::eStage01, mTransitionFlag);
		}
	}

	return this;
}