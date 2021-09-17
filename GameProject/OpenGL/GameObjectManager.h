/*
@file  GameObjectManager.h
@brief ゲームオブジェクトの更新を行う
*/

/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class GameObject;
struct InputState;

#define GAME_OBJECT_MANAGER GameObjectManager::GetInstance()

class GameObjectManager
{
public:

	/*
	@return 自身のインスタンスを返す
	*/
	static GameObjectManager* GetInstance() { return mManager; }

	/*
	@fn インスタンスを生成
	*/
	static void CreateInstance();

	/*
	@fn インスタンスを削除
	*/
	static void DeleteInstance();

	/*
	@fn		ゲームオブジェクトのアップデート処理
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime);

	/*
	@fn		ゲームオブジェクトの入力処理
	@param	_State 各入力機器の入力状態
	@brief	キーボード、マウス、コントローラー
	*/
	void ProcessInput(const InputState& _State);

	/*
	@fn		ゲームオブジェクトの追加
	@param	_object 追加するGameObjectクラスのポインタ
	*/
	void AddGameObject(GameObject* _object);

	/*
	@fn		ゲームオブジェクトの削除
	@param	_object 削除するGameObjectクラスのポインタ
	*/
	void RemoveGameObject(GameObject* _object);

	/*
	@fn		シーンごとの全てのゲームオブジェクトの削除
	@param	_scene 削除するシーンのタグ
	*/
	void RemoveSceneGameObject(SceneBase::Scene _scene);

private:

	/*
	@fn	コンストラクタ
	*/
	GameObjectManager();

	/*
	@fn	デストラクタ
	*/
	~GameObjectManager() {};

	//自身のインスタンス
	static GameObjectManager* mManager;

	//ゲームオブジェクトのポインタの可変長コンテナ
	//カメラを格納するための可変長コンテナ
	std::vector<GameObject*> mCameraObjects;
	//チュートリアル時の全てのゲームオブジェクトを格納するための可変長コンテナ
	std::vector<GameObject*> mTutorialObjects; 
	//ステージ1の時の全てのゲームオブジェクトを格納するための可変長コンテナ
	std::vector<GameObject*> mStage01Objects;
	//ステージ2の時の全てのゲームオブジェクトを格納するための可変長コンテナ
	std::vector<GameObject*> mStage02Objects;
	//Update中に追加されたゲームオブジェクトのポインタを一時的に保存する可変長コンテナ
	std::vector<GameObject*> mPendingGameObjects;

	//Update中かどうか
	bool mUpdatingGameObject;

};
