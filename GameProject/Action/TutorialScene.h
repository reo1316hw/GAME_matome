/*
@brief	�v���v���Z�b�T
*/
#pragma once

/*
@brief	�C���N���[�h
*/
#include "SceneBase.h"

class TutorialVerticalEffect;
class TutorialEffect;

class TutorialScene : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	TutorialScene(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~TutorialScene();

	/*
	@fn	���݂̃V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update() override;

	static bool GetContinueTutorialFlag() { return mSendContinueTutorialFlag; };
	static void SetContinueTutorialFlag(bool _continue) { mSendContinueTutorialFlag = _continue; };

private:

	//�`���[�g���A���V�[�����̏c�ړ����̐����p�l��
	TutorialVerticalEffect* mTutorialVertEffect;
	//�`���[�g���A���V�[�����̑�������p�l��
	TutorialEffect* mTutorialEffect;

	static bool mSendContinueTutorialFlag;

	//�R���e�B�j���[�V�[���Ɉڍs���邩�̃t���O
	bool mContinueTutorialFlag;
};

