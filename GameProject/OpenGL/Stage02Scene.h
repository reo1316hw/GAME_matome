/*
@brief �v���v���Z�b�T
*/
#pragma once

class Stage02Scene : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_NowScene ���݂̃V�[��
	*/
	Stage02Scene(const Scene& _NowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~Stage02Scene();

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

