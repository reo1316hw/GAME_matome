#pragma once
#include "SceneBase.h"
#include "MapCreate.h"
#include "Player.h"
#include "Goal.h"

class HeartUI;

class Stage02Scene : public SceneBase
{
public:
	Stage02Scene(const Scene& _scene);
	~Stage02Scene();

	SceneBase* update() override;
	void       draw() override;

	static bool GetContinueStage02Flag() { return sendContinueStage02Flag; };
	static void SetContinueStage02Flag(bool _continue) { sendContinueStage02Flag = _continue; };

private:
	MapCreate*			mapCreate;
	Player*				player;
	Goal*				goal;
	HeartUI*			heartUI;

	static bool sendContinueStage02Flag;

	bool continueStage02Flag;
	int count;
};

