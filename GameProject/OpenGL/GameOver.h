/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class GameOver : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	GameOver(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~GameOver();

	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update(const InputState& _state) override;

private:
};

