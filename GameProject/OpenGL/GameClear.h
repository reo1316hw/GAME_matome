/*
@brief �v���v���Z�b�T
*/
#pragma once

class GameClear : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	GameClear(const Scene& _nowScene);

	/*
	@fn	�f�X�g���N�^
	*/
	~GameClear();

	/*
	@fn	���݂̃V�[�����ɖ��t���[���X�V����������
	*/
	SceneBase* update(const InputState& _state) override;

private:

};

