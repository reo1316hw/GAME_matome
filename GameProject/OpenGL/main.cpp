/*
@brief �C���N���[�h
*/
#include "pch.h"

#include "Windows.h"

/*
�N���X���ł̐錾���Ԃ�public>protected>private>public(GetSet)�̏�
*/

/*
 @file ��.h
 @brief �ȒP�Ȑ���
*/

/*
   @fn �����Ɋ֐��̐���������
   @brief �v�����
   @param ������ ����
   @return �߂�l�̐���
   @sa �Q�Ƃ��ׂ��֐��������΃����N���\���
   @detail �ڍׂȐ���
 */

/*
	@param ������ ����
*/

/*
  @fn
  @brief
*/

/*
  @fn
*/

/*
   @fn
   @brief
   @return
*/

/*
	 @enum Enum
	 ����
*/

/*
@fn		main�֐�
@param  argc �R�}���h���C�������̐�
@param  argv �R�}���h���C������
*/
int main(int argc, char** argv)
{
	//�Q�[���N���X�̒�`
	Game game;
	//�Q�[���N���X�̏�����������������
	bool success = game.Initialize();
	game.SetFirstScene(new TitleScene(SceneBase::Scene::eTitle));
	if (success)
	{
		game.GameLoop();
	}
	//�Q�[���N���X�̏I������
	game.Termination();

	return 0;
}