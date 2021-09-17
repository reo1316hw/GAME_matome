/*
@brief プリプロセッサ
*/
#pragma once

class UIBase : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_Pos UIの生成場所(スクリーン座標)
	@param	_UiFileName 画像へのアドレス
	@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
	@param	_SceneTag シーンのタグ
	@param	_Scale 画像の拡大サイズ
	*/
	UIBase(const Vector2& _Pos,const std::string& _UiFileName, const SceneBase::Scene _SceneTag, const Tag& _ObjectTag, const float& _Scale = 10);

	/*
	@fn	デストラクタ
	*/
	~UIBase() {};

	/*
	@fn 派生クラスの更新関数を呼び座標に移動量を足し続ける
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

protected:
	
	//UIの描画クラス
	UIComponent* mUI;
	//プレイヤーのポインタ
	Player* mPlayer;
};
