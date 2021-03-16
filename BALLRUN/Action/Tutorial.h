#pragma once
#include "SceneBase.h"
#include "MapCreate.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "Player.h"
#include "ParticleComponent.h"
#include "TutorialVerticalEffect.h"
#include "TutorialEffect.h"
#include "HeartUI.h"
#include "Goal.h"
#include <SDL.h>

class Tutorial : public SceneBase
{
public:
	Tutorial(const Scene& _scene);
	~Tutorial();

	SceneBase* update() override;
	void       draw() override;

	static bool GetContinueTutorialFlag() { return sendContinueTutorialFlag; };
	static void SetContinueTutorialFlag(bool _continue) { sendContinueTutorialFlag = _continue; };

private:
	MapCreate* mapCreate;
	HeartUI* heartUI;
	Player* player;
	TutorialVerticalEffect* tutorialVertEffect;
	TutorialEffect* tutorialEffect;
	Goal* goal;
	Sprite* sprite;

	static bool sendContinueTutorialFlag;

	bool continueTutorialFlag;
	int count;
};

