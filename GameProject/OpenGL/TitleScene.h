/*
@brief �v���v���Z�b�T
*/
#pragma once

class TitleScene : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	TitleScene(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~TitleScene();

	/*
	@fn	���݂̃V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update(const InputState& _state) override;

private:
};

