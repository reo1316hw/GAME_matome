/*
@brief �C���N���[�h
*/
#include "pch.h"

//���g�̃C���X�^���X�̏�����
GameObjectManager* GameObjectManager::mManager = nullptr;

/*
@fn �C���X�^���X�𐶐�
*/
void GameObjectManager::CreateInstance()
{
	if (mManager == nullptr)
	{
		mManager = new GameObjectManager();
		GameObject::CreateMainCamera();
	}
}

/*
@fn �C���X�^���X���폜
*/
void GameObjectManager::DeleteInstance()
{
	if (mManager != nullptr)
	{
		delete mManager;
		mManager = nullptr;
	}
}

/*
@fn		�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g����
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void GameObjectManager::UpdateGameObject(float _deltaTime)
{

	mUpdatingGameObject = true;

	// �J�������X�V����
	for (auto cameraObject : mCameraObjects)
	{
		cameraObject->Update(_deltaTime);
	}

	// �`���[�g���A�����X�V����
	for (auto tutorialObject : mTutorialObjects)
	{
		tutorialObject->Update(_deltaTime);
	}

	// �X�e�[�W�P���X�V����
	for (auto stage01Object : mStage01Objects)
	{
		stage01Object->Update(_deltaTime);
	}

	// �X�e�[�W�Q���X�V����
	for (auto stage02Object : mStage02Objects)
	{
		stage02Object->Update(_deltaTime);
	}

	mUpdatingGameObject = false;

	//�ҋ@���̃I�u�W�F�N�g���X�V���I�u�W�F�N�g�ɒǉ�
	for (auto pending : mPendingGameObjects)
	{
		pending->ComputeWorldTransform();
		if (pending->GetScene() == SceneBase::Scene::eTutorial)
		{
			mTutorialObjects.emplace_back(pending);
		}
		if (pending->GetScene() == SceneBase::Scene::eStage01)
		{
			mStage01Objects.emplace_back(pending);
		}
		if (pending->GetScene() == SceneBase::Scene::eStage02)
		{
			mStage02Objects.emplace_back(pending);
		}
	}
	mPendingGameObjects.clear();
}

/*
@fn		�Q�[���I�u�W�F�N�g�̓��͏���
@param	_State �e���͋@��̓��͏��
@brief	�L�[�{�[�h�A�}�E�X�A�R���g���[���[
*/
void GameObjectManager::ProcessInput(const InputState& _State)
{
	mUpdatingGameObject = true;

	for (auto tutorialObject : mTutorialObjects)
	{
		tutorialObject->ProcessInput(_State);
	}

	for (auto stage01Object : mStage01Objects)
	{
		stage01Object->ProcessInput(_State);
	}

	for (auto stage02Object : mStage02Objects)
	{
		stage02Object->ProcessInput(_State);
	}

	mUpdatingGameObject = false;
}

/*
@fn		�Q�[���I�u�W�F�N�g�̒ǉ�
@param	_object �ǉ�����GameObject�N���X�̃|�C���^
*/
void GameObjectManager::AddGameObject(GameObject* _object)
{
	if (mUpdatingGameObject)
	{
		mPendingGameObjects.emplace_back(_object);
	}
	else
	{
		switch (_object->GetTag())
		{
		case Tag::eCameraTag:
			mCameraObjects.emplace_back(_object);
			break;
		}

		switch (_object->GetScene())
		{
		case SceneBase::Scene::eTutorial:
			mTutorialObjects.emplace_back(_object);
			break;
		case SceneBase::Scene::eStage01:
			mStage01Objects.emplace_back(_object);
			break;
		case SceneBase::Scene::eStage02:
			mStage02Objects.emplace_back(_object);
			break;
		}
	}
}

/*
@fn		�Q�[���I�u�W�F�N�g�̍폜
@param	_object �폜����GameObject�N���X�̃|�C���^
*/
void GameObjectManager::RemoveGameObject(GameObject * _object)
{
	auto iter = std::find(mPendingGameObjects.begin(), mPendingGameObjects.end(), _object);
	if (iter != mPendingGameObjects.end())
	{
		std::iter_swap(iter, mPendingGameObjects.end() - 1);
		mPendingGameObjects.pop_back();
	}

	iter = std::find(mTutorialObjects.begin(), mTutorialObjects.end(), _object);
	if (iter != mTutorialObjects.end())
	{
		std::iter_swap(iter, mTutorialObjects.end() - 1);
		mTutorialObjects.pop_back();
	}

	iter = std::find(mStage01Objects.begin(), mStage01Objects.end(), _object);
	if (iter != mStage01Objects.end())
	{
		std::iter_swap(iter, mStage01Objects.end() - 1);
		mStage01Objects.pop_back();
	}

	iter = std::find(mStage02Objects.begin(), mStage02Objects.end(), _object);
	if (iter != mStage02Objects.end())
	{
		std::iter_swap(iter, mStage02Objects.end() - 1);
		mStage02Objects.pop_back();
	}


}

/*
@fn		�V�[�����Ƃ̑S�ẴQ�[���I�u�W�F�N�g�̍폜
@param	_scene �폜����V�[���̃^�O
*/
void GameObjectManager::RemoveSceneGameObject(SceneBase::Scene _scene)
{
	switch (_scene)
	{
	case SceneBase::Scene::eTutorial:

		while (!mTutorialObjects.empty())
		{
			delete mTutorialObjects.back();
		}
		break;

	case SceneBase::Scene::eStage01:

		while (!mStage01Objects.empty())
		{
			delete mStage01Objects.back();
		}
		break;

	case SceneBase::Scene::eStage02:
		while (!mStage02Objects.empty())
		{
			delete mStage02Objects.back();
		}
		break;
	}
}

/*
@fn	�R���X�g���N�^
*/
GameObjectManager::GameObjectManager()
	: mUpdatingGameObject(false)
{
}