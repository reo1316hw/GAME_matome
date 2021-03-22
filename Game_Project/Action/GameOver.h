#pragma once
#include "SceneBase.h"

class GameOver : public SceneBase
{
public:
	GameOver(const Scene& _scene);
	~GameOver();

	SceneBase* update() override;
private:
};

