/*
@brief �v���v���Z�b�T
*/
#pragma once

class Stage01Scene : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	Stage01Scene(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~Stage01Scene();
 
	/*
	@fn	���݂̃V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update(const InputState& _state) override;

private:

	// �R���e�B�j���[�V�[���Ɉڍs���邩�̃t���O
	bool mTransitionFlag;
};

