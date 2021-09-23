/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_NowScene 現在のシーン
*/
GameOver::GameOver(const Scene& _NowScene)
{
	//環境光
	const Vector3 AmbientLight = Vector3(0.4f, 0.4f, 0.4f);
	//ライトを設定(設定しないと何も映らない)
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
@fn	デストラクタ
*/
GameOver::~GameOver()
{
	delete mSprite;
}

/*
@fn    現在のシーン時に毎フレーム更新処理をする
@param _KeyState 各入力機器の入力状態
*/
SceneBase* GameOver::UpdateScene(const InputState& _KeyState)
{
	//次のシーンに遷移するタイミング
	const int NextSceneTiming = 160;

	mNextSceneCount++;
	if (mNextSceneCount >= NextSceneTiming)
	{
		return new TitleScene(Scene::eTitle);
	}

	return this;
}
