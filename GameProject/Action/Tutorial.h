#pragma once
#include "SceneBase.h"

class TutorialVerticalEffect;
class TutorialEffect;

class Tutorial : public SceneBase
{
public:
	Tutorial(const Scene& _nowScene);
	~Tutorial();

	SceneBase* update() override;

	static bool GetContinueTutorialFlag() { return mSendContinueTutorialFlag; };
	static void SetContinueTutorialFlag(bool _continue) { mSendContinueTutorialFlag = _continue; };

private:
	TutorialVerticalEffect* mTutorialVertEffect;
	TutorialEffect* mTutorialEffect;

	static bool mSendContinueTutorialFlag;

	bool mContinueTutorialFlag;
};

