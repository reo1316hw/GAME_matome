#include "StageSelectScene.h"
#include "Stage01Scene.h"
#include "Renderer.h"

StageSelectScene::StageSelectScene(const Scene& _scene)
{
	// ƒ‰ƒCƒg‚ðÝ’è(Ý’è‚µ‚È‚¢‚Æ‰½‚à‰f‚ç‚È‚¢)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(1.0f, 0.7f, -0.7f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_scene);

	count = 0;
}

StageSelectScene::~StageSelectScene()
{
}

SceneBase* StageSelectScene::update()
{
	count++;

	if (count >= 100)
	{
		/*MapCreate* mapCreate = new MapCreate();
		mapCreate->ClearFile();*/

		return new Stage01Scene(stage01);
	}

	return this;
}

void StageSelectScene::draw()
{
	/*RENDERER->Draw();*/
}
