/*
@brief	�v���v���Z�b�T
*/
#pragma once

/*
@brief	�C���N���[�h
*/

class TutorialScene;
class Stage01Scene;
class Stage02Scene;

class ContinueScene : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	ContinueScene(const Scene& _nowScene, const Scene& _preScene, const bool _transitionSceneFlag);

	/*
	@fn	�f�X�g���N�^
	*/
	~ContinueScene();

	/*
	@fn	���݂̃V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update(const InputState& _state) override;

private:

	//�`���[�g���A���V�[���̃|�C���^
	TutorialScene*	  mTutorial;
	//�X�e�[�W01�V�[���̃|�C���^
	Stage01Scene* mStage01;
	//�X�e�[�W02�V�[���̃|�C���^
	Stage02Scene* mStage02;

	// �`���[�g���A���Ɉڍs���邩�̃t���O
	bool mTutorialTransitionFlag;
	// �X�e�[�W1�Ɉڍs���邩�̃t���O
	bool mStage01TransitionFlag;
	// �X�e�[�W2�Ɉڍs���邩�̃t���O
	bool mStage02TransitionFlag;
};

