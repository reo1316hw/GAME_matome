/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/
#include "SceneBase.h"

class Stage02Scene : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	Stage02Scene(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~Stage02Scene();

	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

	static bool GetContinueStage02Flag() { return mSendContinueStage02Flag; };
	static void SetContinueStage02Flag(bool _continue) { mSendContinueStage02Flag = _continue; };

private:

	static bool mSendContinueStage02Flag;

	//コンティニューシーンに移行するかのフラグ
	bool mContinueStage02Flag;
};

