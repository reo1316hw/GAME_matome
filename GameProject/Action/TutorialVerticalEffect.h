/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/
#include "ParticleEffectBase.h"

class TutorialVerticalEffect : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_pos 縦移動床の説明パネルの座標
	@param	_vel 縦移動床の説明パネルの速度
	@param	_objectTag アタッチしたゲームオブジェクトのタグ
	@param	_sceneTag シーンのタグ
	*/
	TutorialVerticalEffect(const Vector3& _pos, const Vector3& _vel, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~TutorialVerticalEffect() {};

	/*
	@fn		縦移動床の説明パネルのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

};

