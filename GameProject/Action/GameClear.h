/*
@brief	�v���v���Z�b�T
*/
#pragma once

/*
@brief	�C���N���[�h
*/
#include "SceneBase.h"

class GameClear : public SceneBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_nowScene ���݂̃V�[��
	*/
	GameClear(const Scene& _nowScene);
	~GameClear();

	SceneBase* update() override;
private:
};

