/*
@brief インクルード
*/
#include "pch.h"

/*
@param	_Pos UIの生成場所(スクリーン座標)
@param	_uiFileName 画像へのアドレス
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
@param	_Scale 画像の拡大サイズ
*/
UIBase::UIBase(const Vector2& _Pos, const std::string& _UiFileName, const SceneBase::Scene _SceneTag, const Tag& _ObjectTag, const float& _Scale)
	: GameObject(_SceneTag, _ObjectTag)
{

}

/*
@fn 派生クラスの更新関数を呼び座標に移動量を足し続ける
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void UIBase::UpdateGameObject(float _deltaTime)
{

}