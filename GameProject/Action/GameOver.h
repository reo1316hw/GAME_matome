#pragma once
#include "SceneBase.h"

class GameOver : public SceneBase
{
public:
	GameOver(const Scene& _nowScene);
	~GameOver();

	SceneBase* update() override;
private:
};

