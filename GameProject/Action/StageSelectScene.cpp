#include "StageSelectScene.h"
#include "Stage01Scene.h"
#include "Renderer.h"

StageSelectScene::StageSelectScene(const Scene& _nowScene)
{
	// ƒ‰ƒCƒg‚ğİ’è(İ’è‚µ‚È‚¢‚Æ‰½‚à‰f‚ç‚È‚¢)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(1.0f, 0.7f, -0.7f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.m_diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_nowScene);

	mNextSceneCount = 0;
}

StageSelectScene::~StageSelectScene()
{
}

SceneBase* StageSelectScene::update()
{
	mNextSceneCount++;

	if (mNextSceneCount >= 100)
	{
		return new Stage01Scene(stage01);
	}

	return this;
}
