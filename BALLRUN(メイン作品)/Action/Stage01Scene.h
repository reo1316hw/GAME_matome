#pragma once
#include "SceneBase.h"

class Stage01Scene : public SceneBase
{
public:
	Stage01Scene(const Scene& _scene);
	~Stage01Scene();
 
	SceneBase* update() override;

	static bool GetContinueStage01Flag() { return mSendContinueStage01Flag; };
	static void SetContinueStage01Flag(bool _continue) { mSendContinueStage01Flag = _continue; };
private:

	static bool mSendContinueStage01Flag;

	bool mContinueStage01Flag;
	int  mNextSceneCount;
};

