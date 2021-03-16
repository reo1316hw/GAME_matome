#pragma once
#include "Component.h"

/*
@enum PlayerAnimationState
@brief �v���C���[�̃A�N�V������
*/
enum PlayerAnimationState
{
	//�ҋ@
	Idle,
	//�ړ�
	Move,
	//�U��
	Attack,
	//�U�����[�v
	AttackRoop,
	//�������U��
	Range,
	//�������U�����[�v
	RangeRoop,
	//�K�[�h
	Guard,
	//�X�e�b�v
	Avoidance,
	//�_�E��
	Down,
	//��e
	Outi,
	//�W�����v
	Jump,
	//����
	Drop,
};

class AnimationSpriteClip;

/*
@file AnimationPlayerComponent.h
@brief �v���C���[�̃A�j���[�V����
*/
class AnimationPlayerComponent :
	public Component
{
public:
	/*
	@fn �A�j���[�V�����N���X�̊m��
	*/
	AnimationPlayerComponent(GameObject* _owner, int _updateOrder);
	/*
	@fn �A�j���[�V�����N���X�̉��
	*/
	~AnimationPlayerComponent();
	/*
	@fn nowAnimation���X�V���Ȃ���nextAnimation���Q�Ƃ��ύX���s��
	*/
	void Update(float _deltaTime)override;

private:
	//�p�[�e�B�N��
	class ParticleComponent* particleComponent;
	//���ݍĐ����̃A�j���[�V����
	AnimationSpriteClip* nowAnimation;
	//�ҋ@
	AnimationSpriteClip* idle;
	//�ړ�
	AnimationSpriteClip* move;
	//�U��
	AnimationSpriteClip* attack;
	//�U�����[�v
	AnimationSpriteClip* attackRoop;
	//�������U��
	AnimationSpriteClip* rangeAttack;
	//�������U�����[�v
	AnimationSpriteClip* rangeAttackRoop;
	//��e
	AnimationSpriteClip* outi;
	//�K�[�h
	AnimationSpriteClip* guard;
	//�_�E��
	AnimationSpriteClip* down;
	//�W�����v
	AnimationSpriteClip* jump;
	//����
	AnimationSpriteClip* dropping;
	//���
	AnimationSpriteClip* avoidancing;

	//���ݍĐ����̃A�j���[�V������
	PlayerAnimationState nextAnimation;
	//�OF�܂ōĐ����������A�j���[�V������
	PlayerAnimationState beforeAnimation;
public: //�Q�b�^�[�Z�b�^�[
	/*
	@fn ���ɍĐ�����A�j���[�V������ݒ�
	*/
	void SetAnimation(const PlayerAnimationState& _state);
	/*
	@fn �p�[�e�B�N���𔽓]���邩
	*/
	void SetReverce(bool _flag);
};

