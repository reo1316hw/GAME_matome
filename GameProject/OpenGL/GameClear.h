/*
@brief �v���v���Z�b�T
*/
#pragma once

class GameClear : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_NowScene ���݂̃V�[��
	*/
	GameClear(const Scene& _NowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~GameClear();

	/*
	@fn	���݂̃V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* UpdateScene(const InputState& _State) override;

private:

};

