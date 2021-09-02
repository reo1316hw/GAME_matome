/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
GameClear::GameClear(const Scene& _nowScene)
{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(1.0f, 0.7f, -0.7f);
	dir.m_diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_nowScene);

	mInputSystem = new InputSystem();
	mInputSystem->Initialize();

	mSprite = new Sprite("Assets/GameClear.png");

	mNextSceneCount = 0;
}

/*
@fn	デストラクタ
*/
GameClear::~GameClear()
{
	delete mSprite;
}

/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* GameClear::update(const InputState& _state)
{
	mNextSceneCount++;
	if (mNextSceneCount >= 160)
	{
		return new TitleScene(title);
	}

	return this;
}