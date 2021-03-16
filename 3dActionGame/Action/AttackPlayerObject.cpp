#include "AttackPlayerObject.h"
#include "RotateTripleWeaponCombo.h"
#include "ThrowWeaponCombo.h"
#include "ColliderComponent.h"
#include "ComboItemObjectBase.h"
#include "DoubleHammerCombo.h"
#include "UserInterfaceBase.h"
#include "TakeItemEffectUI.h"
#include "TripleSlashSwordCombo.h"
#include "TakeItemUi.h"

const Vector3 AttackPlayerObject::LeftIconPos = Vector3(300, -400, 0);
const Vector3 AttackPlayerObject::RightIconPos = Vector3(500, -400, 0);
const float AttackPlayerObject::IconSize = 0.85f;
const float AttackPlayerObject::BottonSize = 0.3f;

/*
@param _owner �e�I�u�W�F�N�g
*/
AttackPlayerObject::AttackPlayerObject(GameObject* _owner) :
	GameObject(),
	owner(_owner),
	waitTimeForNextAttack(0),
	itemChangeWaitCount(0),
	itemCollided(false)
{
	//���X���b�g��������
	firstSlotAttack = new RotateTripleWeaponCombo();
	//���X���b�g�̕���A�C�R����������
	leftIcon = new UserInterfaceBase(LeftIconPos, firstSlotAttack->GetComboIconFileName());
	leftIcon->SetScale(IconSize);
	//���X���b�g�̑������UI��������
	UserInterfaceBase* xButton = new UserInterfaceBase(LeftIconPos, "Assets/Image/UI/button_x.png", Vector3(BottonSize, BottonSize, BottonSize), 1000);
	//���X���b�g�̏㕔�ɐݒu����g���K�[UI��������
	lButtonIcon = new   UserInterfaceBase(LeftIconPos + Vector3(0, 50, 0), "Assets/Image/UI/bumper1_l1.png", Vector3(BottonSize, BottonSize, BottonSize), 550);
	lButtonGuide = new   UserInterfaceBase(Vector3(-25, 50, 0), "Assets/Image/UI/bumper1_l1.png", Vector3(BottonSize, BottonSize, BottonSize), 500);
	lButtonGuide->SetState(State::Dead);

	//�E�X���b�g��������
	secondSlotAttack = new RotateTripleWeaponCombo();
	//�E�X���b�g�̕���A�C�R����������
	rightIcon = new UserInterfaceBase(RightIconPos, secondSlotAttack->GetComboIconFileName());
	rightIcon->SetScale(IconSize);
	//�E�X���b�g�̑������UI��������
	UserInterfaceBase* yButton = new UserInterfaceBase(RightIconPos, "Assets/Image/UI/button_y.png", Vector3(BottonSize, BottonSize, BottonSize), 1000);
	//�E�X���b�g�̏㕔�ɐݒu����g���K�[UI��������
	rButtonIcon = new   UserInterfaceBase(RightIconPos + Vector3(0, 50, 0), "Assets/Image/UI/bumper1_r1.png", Vector3(BottonSize, BottonSize, BottonSize), 550);
	rButtonGuide = new   UserInterfaceBase(Vector3(25, 50, 0), "Assets/Image/UI/bumper1_r1.png", Vector3(BottonSize, BottonSize, BottonSize), 500);
	rButtonGuide->SetState(State::Dead);

	//�A�C�e���Ƃ̂ݏՓ˂���^�O
	tag = SubPlayerObject;
	//�Փ˃N���X
	ColliderComponent* colliderPair = new ColliderComponent(this, 100, Vector3(30, 30, 30), gameObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
}

AttackPlayerObject::~AttackPlayerObject()
{
}

void AttackPlayerObject::UpdateGameObject(float _deltaTime)
{
	//�e�I�u�W�F�N�g�̈ʒu�Ɉړ�
	SetPosition(owner->GetPosition());
	//�U�����͂��s��ꂸ�ɃR���{��t�P�\���[���ɂȂ����Ƃ�
	if (waitTimeForNextAttack < 0)
	{
		//�R���{��Ԃ����Z�b�g����
		firstSlotAttack->ComboReset();
		//�R���{��Ԃ����Z�b�g����
		secondSlotAttack->ComboReset();
	}
	else
	{
		waitTimeForNextAttack--;
	}
	//�A�C�e���̎擾�C���^�[�o���J�E���g������
	if (itemChangeWaitCount >= 0)
	{
		itemChangeWaitCount--;
	}
	//���炩�̃A�C�e���ƏՓ˂��Ă���Ƃ�
	if (itemCollided)
	{
		//��ʒ����ɃA�C�e���ύX�pUI��ݒu
		lButtonGuide->SetState(State::Active);
		rButtonGuide->SetState(State::Active);
		itemCollided = false;
	}
	else
	{
		//��ʒ����̃A�C�e���ύX�pUI��P��
		lButtonGuide->SetState(State::Dead);
		rButtonGuide->SetState(State::Dead);
	}
}

/*
@fn �ߋ����U��
@param _direction �U�����̃v���C���[�̌���
@param _slot �U���X���b�g
@param _range ���̃R���{���������U�����ǂ���
@return �v���C���[�ɕt�^����s���s�Ȏ���
*/
float AttackPlayerObject::Attack(const float& _direction, const int& _slot, bool& _range)
{
	//�v���C���[�ɕt�^����s���s�Ȏ���
	float playerCanNotMoveTime = 0.0f;

	//�X���b�g������
	if (_slot == 1)
	{
		if (firstSlotAttack != nullptr)
		{
			//�e�I�u�W�F�N�g�̈ʒu�ōU������
			firstSlotAttack->Attack(owner->GetPosition(), _direction, playerCanNotMoveTime, waitTimeForNextAttack);
			//�U���N���X����A�������U���ł��邩���󂯎��
			_range = firstSlotAttack->GetRangeFlag();
		}
	}
	else
	{
		if (secondSlotAttack != nullptr)
		{
			//�e�I�u�W�F�N�g�̈ʒu�ōU������
			secondSlotAttack->Attack(owner->GetPosition(), _direction, playerCanNotMoveTime, waitTimeForNextAttack);
			//�U���N���X����A�������U���ł��邩���󂯎��
			_range = secondSlotAttack->GetRangeFlag();
		}
	}

	return playerCanNotMoveTime;
}

/*
@fn �A�C�e���ƏՓ˂��Ă���Ƃ��ɓ��͂��s���Ă�����U����ύX����
*/
void AttackPlayerObject::OnTriggerStay(ColliderComponent* _colliderPair)
{
	if (_colliderPair->GetObjectTag() == Tag::ComboItem)
	{
		//�A�C�e���擾�̃C���^�[�o�����[���̎�
		if (itemChangeWaitCount <= 0)
		{
			//�擾�p�̓��͂��s���Ă�����
			if (inputLeftChange || inputRightChange)
			{
				//�ύX����A�C�e�������擾
				ComboItemName name = ComboItemObjectBase::SearchComboId(_colliderPair->GetId());
				//���X���b�g�̓���
				if (inputLeftChange)
				{
					//�ݒu����Ă����A�C�e�����A�N�e�B�u�ɂ���
					_colliderPair->GetOwner()->SetState(State::Dead);
					//���ݏ������Ă���N���X�̃A�C�e�������̏�ɒu��
					firstSlotAttack->DropMyItem(position);
					//�擾�����A�C�e���̖��O�����ƂɁA���݂̍U���N���X���J�����V���ȍU���N���X���Z�b�g����
					DropComboItem(name, 1);
					//�擾�����A�C�e���̉摜����ʒ�������擾�����X���b�g�̕����֐i�܂���
					new TakeItemUi(Vector3(0, 0, 0), LeftIconPos, firstSlotAttack->GetComboIconFileName(), Vector3(0.8f, 0.8f, 0.8f));
				}
				//�E�X���b�g�̓���
				else if (inputRightChange)
				{
					//�ݒu����Ă����A�C�e�����A�N�e�B�u�ɂ���
					_colliderPair->GetOwner()->SetState(State::Dead);
					//���ݏ������Ă���N���X�̃A�C�e�������̏�ɒu��
					secondSlotAttack->DropMyItem(position);
					//�擾�����A�C�e���̖��O�����ƂɁA���݂̍U���N���X���J�����V���ȍU���N���X���Z�b�g����
					DropComboItem(name, 2);
					//�擾�����A�C�e���̉摜����ʒ�������擾�����X���b�g�̕����֐i�܂���
					new TakeItemUi(Vector3(0, 0, 0), RightIconPos, secondSlotAttack->GetComboIconFileName(), Vector3(0.8f, 0.8f, 0.8f));
				}

			}
		}
		//�A�C�e���ƏՓ�
		itemCollided = true;
	}
}

/*
@fn ���ݏ������Ă���U���N���X���J�������̍U���N���X�̃A�C�e�������̏�ɐݒu���Ĉ����̍U�����擾����
@param _name �擾�����A�C�e����
@param _slot �ύX���s���U���X���b�g�i���o�[
*/
ComboItemObjectBase* AttackPlayerObject::DropComboItem(const ComboItemName& _name, const int& _slot)
{
	//�A�C�e�����擾�����̂ŃA�C�e���擾�C���^�[�o����ǉ�
	itemChangeWaitCount = 25;
	//���݂̍U���X���b�g���J�����A�C�e���������ƂɍU�����Z�b�g
	switch (_name)
	{
	case(ComboItemName::RotateComboItem):
		DeleteSlot(_slot);
		if (_slot == 1)
		{
			firstSlotAttack = new RotateTripleWeaponCombo;
		}
		else
		{
			secondSlotAttack = new RotateTripleWeaponCombo;
		}
		break;
	case(ComboItemName::ThrowComboItem):
		DeleteSlot(_slot);
		if (_slot == 1)
		{
			firstSlotAttack = new ThrowWeaponCombo;
		}
		else
		{
			secondSlotAttack = new ThrowWeaponCombo;
		}
		break;
	case(ComboItemName::HammerComboItem):
		DeleteSlot(_slot);
		if (_slot == 1)
		{
			firstSlotAttack = new DoubleHammerCombo;
		}
		else
		{
			secondSlotAttack = new DoubleHammerCombo;
		}
		break;
	case(ComboItemName::SlashSwordComboItem):
		DeleteSlot(_slot);
		if (_slot == 1)
		{
			firstSlotAttack = new TripleSlashSwordCombo;
		}
		else
		{
			secondSlotAttack = new TripleSlashSwordCombo;
		}
		break;
	}
	if (_slot == 1)
	{
		leftIcon = new UserInterfaceBase(LeftIconPos, firstSlotAttack->GetComboIconFileName(), Vector3(IconSize, IconSize, IconSize), 150);
		new TakeItemEffectUI(LeftIconPos);
	}
	else
	{
		rightIcon = new UserInterfaceBase(RightIconPos, secondSlotAttack->GetComboIconFileName(), Vector3(IconSize, IconSize, IconSize), 150);
		new TakeItemEffectUI(RightIconPos);
	}
	return nullptr;
}

/*
@fn�@�X���b�g���������
@param _slot ����������X���b�g�i���o�[
*/
void AttackPlayerObject::DeleteSlot(const int& _slot)
{
	if (_slot == 1)
	{
		if (firstSlotAttack != nullptr)
		{
			delete firstSlotAttack;
		}
		if (leftIcon != nullptr)
		{
			delete leftIcon;
		}
	}
	else
	{
		if (secondSlotAttack != nullptr)
		{
			delete secondSlotAttack;
		}
		if (rightIcon != nullptr)
		{
			delete rightIcon;
		}
	}
}
