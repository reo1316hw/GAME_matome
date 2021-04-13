#pragma once
#include "SceneBase.h"

class Stage02Scene : public SceneBase
{
public:
	Stage02Scene(const Scene& _nowScene);
	~Stage02Scene();

	SceneBase* update() override;

	static bool GetContinueStage02Flag() { return mSendContinueStage02Flag; };
	static void SetContinueStage02Flag(bool _continue) { mSendContinueStage02Flag = _continue; };

private:

	static bool mSendContinueStage02Flag;

	bool mContinueStage02Flag;
	int mCount;
};

