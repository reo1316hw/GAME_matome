/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/
#include "SceneBase.h"

class GameClear : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	GameClear(const Scene& _nowScene);
	~GameClear();

	SceneBase* update() override;
private:
};

