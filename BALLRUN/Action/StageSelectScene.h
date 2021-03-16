#pragma once
#include "SceneBase.h"

class StageSelectScene : public SceneBase
{
public:
	StageSelectScene(const Scene& _scene);
	~StageSelectScene();

	SceneBase* update() override;
	void       draw() override;
private:
	int count;
};

