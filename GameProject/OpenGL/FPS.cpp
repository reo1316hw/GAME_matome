/*
@file  FPS.h
@brief �t���[���ɂ����������Ԃ��v���������݂���N���X
*/

/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn	�R���X�g���N�^
*/
FPS::FPS()
	: MSetFps(60)
	, MOneFrameTickCount(1000 / MSetFps)
	, mFpsCount(0)
	, mFrameStartTickTime(0)
	, mFps(0)
    , mBeforetickCount(0)
	, mDeltaTime(0)
{

}

/*
@fn	�f�X�g���N�^
*/
FPS::~FPS()
{
}

/*
@fn	�t���[�����̏���
*/
void FPS::Update()
{
	Wait();
	mDeltaTime = (SDL_GetTicks() - mBeforetickCount) / 1000.0f;
	if (mDeltaTime >= 0.10f)
	{
		mDeltaTime = 0.10f;
	}
	mBeforetickCount = SDL_GetTicks();
	//1�t���[���ڂ̎�����ۑ�
	if (mFpsCount == 0)
	{
		mFrameStartTickTime = SDL_GetTicks();
	}
	//�ݒ肵���t���[�������o�߂�����
	if (mFpsCount == MSetFps)
	{
		int nowTickTime = SDL_GetTicks();
		mFps = 1000 / ((nowTickTime - mFrameStartTickTime) / MSetFps);
		mFpsCount = 0;
	}
	else
	{
		mFpsCount++;
	}
}

/*
@fn	FPS���ݒ�l���傫���Ȃ�Ȃ����߂̐���
*/
void FPS::Wait()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mBeforetickCount + MOneFrameTickCount));
}
