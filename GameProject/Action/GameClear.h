#pragma once
#include "SceneBase.h"

class GameClear : public SceneBase
{
public:
	GameClear(const Scene& _scene);
	~GameClear();

	SceneBase* update() override;
private:
};

