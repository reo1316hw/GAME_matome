/*
@brief �v���v���Z�b�T
*/
#pragma once

class GameOverScene : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_NowScene ���݂̃V�[��
	*/
	GameOverScene(const Scene& _NowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~GameOverScene();

	/*
	@fn    ���݂̃V�[�����ɖ��t���[���X�V����������
	@param _KeyState �e���͋@��̓��͏��
	*/
	SceneBase* UpdateScene(const InputState& _KeyState) override;

private:
};

