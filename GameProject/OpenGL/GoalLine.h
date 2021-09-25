/*
@brief プリプロセッサ
*/
#pragma once

class GoalLine : public ParticleEffectBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos ゴールラインの座標
	@param	_Vel ゴールラインの速度
	@param	_TextureName テクスチャデータのパス
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
    @param	_playerPtr プレイヤーのポインタ
	*/
	GoalLine(const Vector3& _Pos, const Vector3& _Vel,const std::string& _TextureName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
	@fn	デストラクタ
	*/
	~GoalLine() {};

	/*
	@fn		ゴールラインのアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	Player* mPlayer;
};

