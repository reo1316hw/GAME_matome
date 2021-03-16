#include "TestComponent.h"
#include "GameObject.h"

TestComponent::TestComponent(GameObject* _owner, int _updateOrder):
	Component(_owner,_updateOrder)
{

}

TestComponent::~TestComponent()
{
}

void TestComponent::Update(float _deltaTime)
{
	//�eGameObject�̍��W�Ɍ��̍��W����x������-10�������W�𑫂�
	owner->SetPosition(owner->GetPosition() + Vector3(-10, 0, 0));
}
