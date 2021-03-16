#include "HeartUI.h"
#include "Renderer.h"
#include "Player.h"

HeartUI::HeartUI(const Vector2& _pos, SceneBase::Scene _sceneTag, const Tag& _objectTag)
	:UIBase(_pos, "Assets/heart02.png", _sceneTag, _objectTag)
{
	ui = new UIComponent(this);
	ui->SetTexture(RENDERER->GetTexture("Assets/heart.png"));

	position = Vector3(_pos.x, _pos.y, 0.0f);

}

void HeartUI::UpdateGameObject(float _deltaTime)
{
	if (player->GetLife() == 2)
	{
		if (ui->GetUIid() == 2 || ui->GetUIid() == 5 || ui->GetUIid() == 8)
		{
			ui->SetVisible(false);

		}
	}

	if (player->GetLife() == 1)
	{
		if (ui->GetUIid() == 1 || ui->GetUIid() == 4 || ui->GetUIid() == 7)
		{
			ui->SetVisible(false);

		}
	}

	if (player->GetLife() == 0)
	{
		if (ui->GetUIid() == 0 || ui->GetUIid() == 3 || ui->GetUIid() == 6)
		{
			ui->SetVisible(false);
		}
	}
}
