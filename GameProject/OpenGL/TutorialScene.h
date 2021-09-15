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
	SceneBase* update(const InputState& _state) override;

private:

	//�`���[�g���A���V�[�����̏c�ړ����̐����p�l��
	VerticalMoveGroundExplanationBoard* mVerticalMoveGroundExplanationBoard;
	//�`���[�g���A���V�[�����̑�������p�l��
	OperationExplanationBoard* mOperationExplanationBoard;

	// �R���e�B�j���[�V�[���Ɉڍs���邩�̃t���O
	bool mTransitionFlag;
};