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
private:
	Tutorial*	  mTutorial;
	Stage01Scene* mStage01;
	Stage02Scene* mStage02;
};

