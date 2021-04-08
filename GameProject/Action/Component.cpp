#include "Component.h"
#include "GameObject.h"

/*
@fn		�R���X�g���N�^
@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
*/
Component::Component(GameObject* _owner, int _updateOrder)
	: mOwner(_owner)
	, mUpdateOrder(_updateOrder)
{
	mOwner->AddComponent(this);
}

/*
@fn	�f�X�g���N�^
*/
Component::~Component()
{
	mOwner->RemoveComponent(this);
}

/*
@fn		�t���[�����̏���
@param	�Ō�̃t���[������������̂ɗv��������
*/
void Component::Update(float _deltaTime)
{
}
