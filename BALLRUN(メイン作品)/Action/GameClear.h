#pragma once
#include "SceneBase.h"

class GameClear : public SceneBase
{
public:
	GameClear(const Scene& _scene);
	~GameClear();

	SceneBase* update() override;
	void       draw() override;
private:

	int count;
};

