#pragma once
#include "UIComponent.h"
#include "UIBase.h"

class Player;

class HeartUI :public UIBase
{
public:
	HeartUI(const Vector2& _pos, SceneBase::Scene _sceneTag, const Tag& _objectTag);
	~HeartUI() {};

	void UpdateGameObject(float _deltaTime)override;

private:

	UIComponent* ui;
	Player* player;
};