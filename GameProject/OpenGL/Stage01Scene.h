/*
@brief �v���v���Z�b�T
*/
#pragma once

class Stage01Scene : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_NowScene ���݂̃V�[��
	*/
	Stage01Scene(const Scene& _NowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~Stage01Scene();
 
	/*
	@fn	���݂̃V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* UpdateScene(const InputState& _State) override;

private:

	// �R���e�B�j���[�V�[���Ɉڍs���邩�̃t���O
	bool mTransitionFlag;
};

