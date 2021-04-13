#pragma once
#include "SceneBase.h"

class StageSelectScene : public SceneBase
{
public:
	StageSelectScene(const Scene& _nowScene);
	~StageSelectScene();

	SceneBase* update() override;
private:
};

