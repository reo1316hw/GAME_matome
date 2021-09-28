/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos プレイヤーの体力UIの生成場所(スクリーン座標)
@param	_ObjectTag アタッチしたゲームオブジェクトのタグ
@param	_SceneTag シーンのタグ
@param _playerPtr プレイヤーのポインタ
*/
HeartUI::HeartUI(const Vector2& _Pos, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
	:UIBase(_Pos, "Assets/heart02.png", _SceneTag, _ObjectTag)
{
	mUI = new UIComponent(this);
	mUI->SetTexture(RENDERER->GetTexture("Assets/UI/Heart.png"));

	mPosition = Vector3(_Pos.x, _Pos.y, 0.0f);

	mPlayer = _playerPtr;
}

/*
@fn		プレイヤーの体力UIのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void HeartUI::UpdateGameObject(float _deltaTime)
{
	if (mPlayer->GetLife() == 2)
	{
		if (mUI->GetUIid() == 2 || mUI->GetUIid() == 5 || mUI->GetUIid() == 8)
		{
			mUI->SetVisible(false);

		}
	}

	if (mPlayer->GetLife() == 1)
	{
		if (mUI->GetUIid() == 1 || mUI->GetUIid() == 4 || mUI->GetUIid() == 7)
		{
			mUI->SetVisible(false);

		}
	}

	if (mPlayer->GetLife() == 0)
	{
		if (mUI->GetUIid() == 0 || mUI->GetUIid() == 3 || mUI->GetUIid() == 6)
		{
			mUI->SetVisible(false);
		}
	}
}
