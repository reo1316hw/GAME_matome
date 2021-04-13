#pragma once
#include "SceneBase.h"

class TitleScene : public SceneBase
{
public:
	TitleScene(const Scene& _nowScene);
	~TitleScene();

	SceneBase* update() override;
private:
};

