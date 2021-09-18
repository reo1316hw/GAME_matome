/*
@file ParticleEffectBase.h
@brief 一定時間で消える、主にエフェクトの基底クラスとして使用されるクラス
*/

/*
@brief プリプロセッサ
*/
#pragma once

/*
@enum	パーティクルの状態
*/
enum ParticleState
{
	//アクティブ
	eParticleActive,
	//無効にする
	eParticleDisable,
};

class ParticleEffectBase : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos エフェクトの生成場所
	@param	_Vel エフェクトの速度
	@param	_LifeCount エフェクトの生存時間
	@param	_ParticleFileName 画像へのアドレス
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	@param	_Scale 画像の拡大サイズ
	*/
	ParticleEffectBase(const Vector3& _Pos, const Vector3& _Vel, const int& _LifeCount, const std::string& _ParticleFileName, const SceneBase::Scene _SceneTag, const Tag& _ObjectTag,const float& _Scale = 10);

	/*
	@fn	デストラクタ
	*/
	virtual ~ParticleEffectBase() {};

	/*
	@fn		派生クラスの更新関数を呼び座標に移動量を足し続ける
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

protected:

	/*
	@fn 生存時間をカウントダウンする関数。派生クラスで更新関数を決定した場合そこに追加すること。
	*/
	void LifeCountDown();

	//パーティクルの描画クラス
	ParticleComponent*	mParticle;
	//パーティクルの状態
	ParticleState		mParticleState;

	//生存時間
	int					mLifeCount;

	//アルファ値
	float				mAlpha;
	//大きさ
	float				mScale;
	//加速度
	float				mSpeed;

public:

	/*
	@param _flag 反転を行うか
	*/
	void SetReverve(float _flag);
};
