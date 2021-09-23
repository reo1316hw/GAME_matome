/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class VerticalMoveGroundExplanationBoard;
class OperationExplanationBoard;

class TutorialScene : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_NowScene ���݂̃V�[��
	*/
	TutorialScene(const Scene& _NowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~TutorialScene();

	/*
	@fn    ���݂̃V�[�����ɖ��t���[���X�V����������
	@param _KeyState �e���͋@��̓��͏��
	*/
	SceneBase* UpdateScene(const InputState& _KeyState) override;

private:

	//�`���[�g���A���V�[�����̏c�ړ����̐����p�l��
	VerticalMoveGroundExplanationBoard* mVerticalMoveGroundExplanationBoard;
	//�`���[�g���A���V�[�����̑�������p�l��
	OperationExplanationBoard* mOperationExplanationBoard;
	//�e�S�[�����C���̃|�C���^
	GoalLineRoot* mGoalLineRoot;

	// �R���e�B�j���[�V�[���Ɉڍs���邩�̃t���O
	bool mTransitionFlag;
};