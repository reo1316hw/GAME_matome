/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_NowScene ���݂̃V�[��
*/
TutorialScene::TutorialScene(const Scene& _NowScene)
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

	mSprite = new Sprite("Assets/forest.png");

	mMapCreate = new MapCreate();
	mPlayer = mMapCreate->OpenTutorialFile();

	//�e�S�[�����C���̍��㌴�_
	const Vector3 TopLeftOriginGoalLine = Vector3(300.0f, 200.0f, -75800.0f);
	//�e�S�[�����C���𐶐�
	mGoalLineRoot = new GoalLineRoot(TopLeftOriginGoalLine, _NowScene, mPlayer);

	//��������{�[�h����
	mOperationExplanationBoard = new OperationExplanationBoard(Vector3(0, 200, -96000), Vector3::sZERO, Tag::eOtherTag, _NowScene);
	//�c�ړ��������{�[�h����
	mVerticalMoveGroundExplanationBoard = new VerticalMoveGroundExplanationBoard(Vector3(0, 200, -92000), Vector3::sZERO, Tag::eOtherTag, _NowScene);

	//�̗�UI����
	for (int i = 0; i < 3; i++)
	{
		mHeartUI = new HeartUI(Vector2(i * 100.0f, 50.0f), Tag::eOtherTag, Scene::eTutorial, mPlayer);
	}
}

/*
@fn	�f�X�g���N�^
*/
TutorialScene::~TutorialScene()
{
	GAME_OBJECT_MANAGER->RemoveSceneGameObject(Scene::eTutorial);
	delete mSprite;
	delete mMapCreate;
	delete mGoalLineRoot;
}

/*
@fn    ���݂̃V�[�����ɖ��t���[���X�V����������
@param _KeyState �e���͋@��̓��͏��
*/
SceneBase* TutorialScene::UpdateScene(const InputState& _KeyState)
{
	//���̃V�[���ɑJ�ڂ���^�C�~���O
	const int NextSceneTiming = 80;

	if (mPlayer->GetClearFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= NextSceneTiming)
		{
			return new Stage01Scene(Scene::eStage01);
		}
	}

	if (mPlayer->GetDeathFlag())
	{
		mNextSceneCount++;

		if (mNextSceneCount >= NextSceneTiming)
		{
			mTransitionFlag = true;
			return new ContinueScene(Scene::eContinue, Scene::eTutorial, mTransitionFlag);
		}
	}

	return this;
}