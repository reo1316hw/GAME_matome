#pragma once
#include "Component.h"

//���Ɉړ���������GameObject�̕⏕�N���X
class TestComponent :
	public Component
{
public:
	TestComponent(GameObject* _owner, int _updateOrder = 100);
	~TestComponent();

	void Update(float _deltaTime)override;
};

