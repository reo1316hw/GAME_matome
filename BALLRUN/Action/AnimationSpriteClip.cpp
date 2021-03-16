#include "AnimationSpriteClip.h"
#include "Texture.h"

/*
 @fn �������Ă���S�̃A�j���[�V�����̏�����
*/
AnimationSpriteClip::AnimationSpriteClip() :
	nowAnimationCount(0),
	nowAnimationTime(0),
	loop(false),
	animationEnd(false)
{
	animation = new AnimationKeyFrame[10];
	for (int num = 0; num < 10; num++)
	{
		animation[num].sprite = nullptr;
		animation[num].waitTimeForNextTexture = 0;
	}
}

/*
 @fn �������Ă���S�̃A�j���[�V�����̉��
*/
AnimationSpriteClip::~AnimationSpriteClip()
{
	if (animation != nullptr)
	{
		delete[] animation;
	}
}

/*
 @fn �A�j���[�V�������s��
*/
void AnimationSpriteClip::Animation()
{
	//�A�j���[�V�������I�����Ă��Ă����[�v���邩�����łȂ���
	if (animationEnd&&!loop)
	{
		return;
	}
	//���݂̃A�j���[�V�����J�E���g���Đ����̃e�N�X�`���\�����Ԃ𒴂��Ă��Ȃ���
	if (nowAnimationTime < animation[nowAnimationCount].waitTimeForNextTexture)
	{
		nowAnimationTime++;
	}
	//�������ꍇ
	else
	{
		//���̃A�j���[�V������
		nowAnimationCount++;
		//���̃A�j���[�V���������݂��Ȃ��ꍇnullptr���Ԃ��Ă���̂ŏI��
		if (animation[nowAnimationCount].sprite == nullptr)
		{
			//�A�j���[�V�����I��
			animationEnd = true;
			//���[�v���邩�A����ꍇ�Đ�������������
			if (loop)
			{
				nowAnimationCount = 0;
			}
			else
			{
				nowAnimationCount--;
			}
		}
		nowAnimationTime = 0;
	}
}

/*
 @fn �A�j���[�V���������Z�b�g
*/
void AnimationSpriteClip::ResetAnimation()
{
	nowAnimationCount = 0;
	nowAnimationTime = 0;
	animationEnd = false;
}
