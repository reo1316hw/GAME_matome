#pragma once
#include "GameObject.h"
#include "ComboItemObjectBase.h"

/*
@file AttackPlayerObject.h
@brief Player�ɋߐڃR���{�A�������U�����s�킹��N���X
*/
class AttackPlayerObject :
	public GameObject
{
public:
	/*
	@param _owner �e�I�u�W�F�N�g
	*/
	AttackPlayerObject(GameObject* _owner);
	~AttackPlayerObject();
	void UpdateGameObject(float _deltaTime)override;
	void SetInput(const bool& _lInput, const bool& _rInput) { inputLeftChange = _lInput; inputRightChange =_rInput; }
	/*
	@fn �ߋ����U��
	@param _direction �U�����̃v���C���[�̌���
	@param _slot �U���X���b�g
	@param _range ���̃R���{���������U�����ǂ���
	@return �v���C���[�ɕt�^����s���s�Ȏ���
	*/
	float Attack(const float& _direction, const int& _slot, bool& _range);
private:
	/*
	@fn �A�C�e���ƏՓ˂��Ă���Ƃ��ɓ��͂���������U���X���b�g��ύX�����̃A�C�e�������̏�ɗ���������
	*/
	void OnTriggerStay(ColliderComponent* _colliderPair) ;
	/*
	@fn ���ݏ������Ă���U���N���X���J�������̍U���N���X�̃A�C�e�������̏�ɐݒu���Ĉ����̍U�����擾����
	@param _name �擾�����A�C�e����
	@param _slot �ύX���s���U���X���b�g�i���o�[
	*/
	ComboItemObjectBase* DropComboItem(const ComboItemName& _name,const int& slot);

	/*
	@fn�@�X���b�g���������
	@param _slot ����������X���b�g�i���o�[
	*/
	void DeleteSlot(const int& _slot);
	//�X���b�g�Q�̃A�C�R�����W
	static const Vector3 RightIconPos;
	//�ۯĂP�̃A�C�R�����W
	static const Vector3 LeftIconPos;
	//�A�C�R�����֎q
	static const float IconSize;
	//�X���b�g�A�C�R���ɂ��Ԃ��鑀��{�^���̃T�C�Y
	static const float BottonSize;
	//���X���b�g��ύX����̂ɕK�v�ȃ{�^��
	bool inputLeftChange;
	//�E�X���b�g��ύX����̂ɕK�v�ȃ{�^��
	bool inputRightChange;
	//�e�I�u�W�F�N�g
	GameObject* owner;
	//���O�����s���U���X���b�g
	class ComboMeanPlayerBase* firstSlotAttack;
	//���O�����s���U���X���b�g
	class ComboMeanPlayerBase* secondSlotAttack;
	//�ߋ����U���̃R���{�����ɂȂ���P�\���ԁB���ꂪ0�ɂȂ�ƃR���{��Ԃ����Z�b�g����
	float waitTimeForNextAttack;

	//�U���̕ύX�ɗp����A�A�C�e���̎擾�C���^�[�o���J�E���g
	int itemChangeWaitCount;
	//���X���b�g�̃A�C�R��
	class UserInterfaceBase* leftIcon;
	//�E�ۯẴA�C�R��
	class UserInterfaceBase* rightIcon;
	//�I�u�W�F�N�g�t�߂ɕ\������K�C�h�{�^��
	class UserInterfaceBase* lButtonGuide;
	//���X���b�g�̃A�C�e����\������A�C�R��
	class UserInterfaceBase* lButtonIcon;
	//�I�u�W�F�N�g�t�߂ɕ\������K�C�h�{�^��
	class UserInterfaceBase* rButtonGuide;
	//�E�X���b�g�̃A�C�e����\������A�C�R��
	class UserInterfaceBase* rButtonIcon;
	//�A�C�e���ƏՓ˂��Ă��邩�B�Փ˂��Ă���Ƃ���GuideUI��\��������
	bool itemCollided;
};

/*
���U���N���X�̒ǉ��菇
�@��⌕�̂悤�ȁA�e�X�̋����݂̂𐧌䂷�镐��N���X:GameObject���쐬
�A����N���X���󂯂Ƃ������W�A�����ɔ���������U���N���X:AttackBase���쐬
�B�U���N���X���R���{���Ƃɐ�������R���{�N���X:ComboMeanPlayerBase���쐬
~�t���ւ����s���ꍇ~
�CComboItemObjectBase���̗񋓌^�Ő錾
�D���̃N���XAttackPlayerObject���ł��̍U���N���X��t���ւ��邽�ߊ֐��ɕ��͂�������
*/
