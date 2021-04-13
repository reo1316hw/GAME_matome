/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/
#include "SceneBase.h"

class Stage01Scene : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	Stage01Scene(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~Stage01Scene();
 
	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

	static bool GetContinueStage01Flag() { return mSendContinueStage01Flag; };
	static void SetContinueStage01Flag(bool _continue) { mSendContinueStage01Flag = _continue; };

private:

	static bool mSendContinueStage01Flag;

	//コンティニューシーンに移行するかのフラグ
	bool mContinueStage01Flag;
};

