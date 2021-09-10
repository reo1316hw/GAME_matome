/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_pos プレイヤーの体力UIの生成場所(スクリーン座標)
@param	_objectTag アタッチしたゲームオブジェクトのタグ
@param	_sceneTag シーンのタグ
@param _playerPtr プレイヤーのポインタ
*/
HeartUI::HeartUI(const Vector2& _pos, const Tag& _objectTag, SceneBase::Scene _sceneTag, Player* _playerPtr)
	:UIBase(_pos, "Assets/heart02.png", _sceneTag, _objectTag)
{
	mUI = new UIComponent(this);
	mUI->SetTexture(RENDERER->GetTexture("Assets/heart.png"));

	mPosition = Vector3(_pos.x, _pos.y, 0.0f);

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
