#pragma once
#include "SceneBase.h"

class Tutorial;
class Stage01Scene;
class Stage02Scene;

class ContinueScene :
	public SceneBase
{
public:
	ContinueScene(const Scene& _scene);
	~ContinueScene();

	SceneBase* update() override;
	void       draw() override;
private:
	Tutorial* tutorial;
	Stage01Scene* stage01;
	Stage02Scene* stage02;

	int scene;
	int count;
};

