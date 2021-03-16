#include "GameObjectManager.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "Renderer.h"
#include "MainCameraObject.h"
#include "SceneBase.h"

GameObjectManager* GameObjectManager::manager = nullptr;

/*
@fn インスタンスを生成
*/
void GameObjectManager::CreateInstance()
{
	if (manager == nullptr)
	{
		manager = new GameObjectManager();
		GameObject::CreateMainCamera();
	}
}

/*
@fn インスタンスを削除
*/
void GameObjectManager::DeleteInstance()
{
	if (manager != nullptr)
	{
		delete manager;
		manager = nullptr;
	}
}

/*
@brief  ゲームオブジェクトのアップデート処理
*/
void GameObjectManager::UpdateGameObject(float _deltaTime)
{

	updatingGameObject = true;

	// カメラを更新する
	for (auto cameraObject : cameraObjects)
	{
		cameraObject->Update(_deltaTime);
	}

	// チュートリアルを更新する
	for (auto tutorialObject : tutorialObjects)
	{
		tutorialObject->Update(_deltaTime);
	}

	// ステージ１を更新する
	for (auto stage01Object : stage01Objects)
	{
		stage01Object->Update(_deltaTime);
	}

	// ステージ２を更新する
	for (auto stage02Object : stage02Objects)
	{
		stage02Object->Update(_deltaTime);
	}

	updatingGameObject = false;

	//待機中のオブジェクトを更新中オブジェクトに追加
	for (auto pending : pendingGameObjects)
	{
		pending->ComputeWorldTransform();
		if (pending->GetScene() == SceneBase::Scene::tutorial)
		{
			tutorialObjects.emplace_back(pending);
		}
		if (pending->GetScene() == SceneBase::Scene::stage01)
		{
			stage01Objects.emplace_back(pending);
		}
		if (pending->GetScene() == SceneBase::Scene::stage02)
		{
			stage02Objects.emplace_back(pending);
		}
	}
	pendingGameObjects.clear();
}
/*
@brief  ゲームオブジェクトの入力処理
*/
void GameObjectManager::ProcessInput(const InputState& _state)
{
	updatingGameObject = true;

	for (auto tutorialObject : tutorialObjects)
	{
		tutorialObject->ProcessInput(_state);
	}

	for (auto stage01Object : stage01Objects)
	{
		stage01Object->ProcessInput(_state);
	}

	for (auto stage02Object : stage02Objects)
	{
		stage02Object->ProcessInput(_state);
	}


	updatingGameObject = false;
}

/*
@brief  ゲームオブジェクトの追加
@param	追加するGameObjectクラスのポインタ
*/
void GameObjectManager::AddGameObject(GameObject* _object)
{
	if (updatingGameObject)
	{
		pendingGameObjects.emplace_back(_object);
	}
	else
	{
		switch (_object->GetTag())
		{
		case Camera:
			cameraObjects.emplace_back(_object);
			break;
		}

		switch (_object->GetScene())
		{
		case SceneBase::tutorial:
			tutorialObjects.emplace_back(_object);
			break;
		case SceneBase::stage01:
			stage01Objects.emplace_back(_object);
			break;
		case SceneBase::stage02:
			stage02Objects.emplace_back(_object);
			break;
		}
	}
}

/*
@brief  ゲームオブジェクトの削除
@param	削除するGameObjectクラスのポインタ
*/
void GameObjectManager::RemoveGameObject(GameObject * _object)
{
	auto iter = std::find(pendingGameObjects.begin(), pendingGameObjects.end(), _object);
	if (iter != pendingGameObjects.end())
	{
		std::iter_swap(iter, pendingGameObjects.end() - 1);
		pendingGameObjects.pop_back();
	}

	iter = std::find(tutorialObjects.begin(), tutorialObjects.end(), _object);
	if (iter != tutorialObjects.end())
	{
		std::iter_swap(iter, tutorialObjects.end() - 1);
		tutorialObjects.pop_back();
	}

	iter = std::find(stage01Objects.begin(), stage01Objects.end(), _object);
	if (iter != stage01Objects.end())
	{
		std::iter_swap(iter, stage01Objects.end() - 1);
		stage01Objects.pop_back();
	}

	iter = std::find(stage02Objects.begin(), stage02Objects.end(), _object);
	if (iter != stage02Objects.end())
	{
		std::iter_swap(iter, stage02Objects.end() - 1);
		stage02Objects.pop_back();
	}


}

void GameObjectManager::RemoveGameObjects(SceneBase::Scene _scene)
{
	switch (_scene)
	{
	case SceneBase::tutorial:

		while (!tutorialObjects.empty())
		{
			delete tutorialObjects.back();
		}
		break;

	case SceneBase::stage01:

		while (!stage01Objects.empty())
		{
			delete stage01Objects.back();
		}
		break;

	case SceneBase::stage02:
		while (!stage02Objects.empty())
		{
			delete stage02Objects.back();
		}
		break;
	}
}

/*
@brief 使用したすべてのゲームオブジェクトを解放する
@detail シーン遷移の際に使用される。GameObject内の再利用フラグが建っているオブジェクトは解放しない
*/
//void GameObjectManager::RemoveAllUsedGameObject()
//{
//	std::vector<GameObject*> reUseObjects;
//
//	while (!gameObjects.empty())
//	{
//		GameObject* obj = gameObjects.back();
//		if (obj->GetReUseGameObject())
//		{
//			reUseObjects.push_back(obj);
//			gameObjects.pop_back();
//			continue;
//		}
//		delete obj;
//	}
//
//	while (!cameraObjects.empty())
//	{
//		GameObject* obj = cameraObjects.back();
//		if (obj->GetReUseGameObject())
//		{
//			reUseObjects.push_back(obj);
//			cameraObjects.pop_back();
//			continue;
//		}
//		delete obj;
//	}
//}

//GameObject * GameObjectManager::FindGameObject(Tag _tag)
//{
//	for (auto itr : gameObjects)
//	{
//		if (itr->GetTag() == _tag)
//		{
//			return itr;
//		}
//	}
//
//	return nullptr;
//}


//std::vector<GameObject*> GameObjectManager::FindGameObjects(Tag _tag)
//{
//	std::vector<GameObject*> ret;
//	for (auto itr : gameObjects)
//	{
//		if (itr->GetTag() == _tag)
//		{
//			ret.push_back(itr);
//		}
//	}
//	return ret;
//}


GameObjectManager::GameObjectManager()
	: updatingGameObject(false)
{
}


GameObjectManager::~GameObjectManager()
{
	/*while (!gameObjects.empty())
	{
		delete gameObjects.back();
	}*/
}