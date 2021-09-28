/*
@brief �v���v���Z�b�T
*/
#pragma once

class SecondStageScene : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_NowScene ���݂̃V�[��
	*/
	SecondStageScene(const Scene& _NowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~SecondStageScene();

	/*
	@fn    ���݂̃V�[�����ɖ��t���[���X�V����������
	@param _KeyState �e���͋@��̓��͏��
	*/
	SceneBase* UpdateScene(const InputState& _KeyState) override;

private:

	//�e�S�[�����C���̃|�C���^
	GoalLineRoot* mGoalLineRoot;
	//�S�[�����[�v��
	GoalWarpBorard* mGoalWarpBorard;

	// �R���e�B�j���[�V�[���Ɉڍs���邩�̃t���O
	bool mTransitionFlag;
};

