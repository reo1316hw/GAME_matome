#pragma once
#include "SceneBase.h"
#include "MapCreate.h"
#include "Player.h"
#include "Goal.h"

class HeartUI;

class Stage01Scene : public SceneBase
{
public:
	Stage01Scene(const Scene& _scene);
	~Stage01Scene();
 
	SceneBase* update() override;
	void       draw() override;

	static bool GetContinueStage01Flag() { return sendContinueStage01Flag; };
	static void SetContinueStage01Flag(bool _continue) { sendContinueStage01Flag = _continue; };
private:
	MapCreate*		   mapCreate;
	Player*			   player;
	Goal* goal;
	HeartUI* heartUI;

	static bool sendContinueStage01Flag;

	bool continueStage01Flag;
	int count;
};

