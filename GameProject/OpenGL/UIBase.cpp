/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@param	_Pos UI�̐����ꏊ(�X�N���[�����W)
@param	_uiFileName �摜�ւ̃A�h���X
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
@param	_Scale �摜�̊g��T�C�Y
*/
UIBase::UIBase(const Vector2& _Pos, const std::string& _UiFileName, const SceneBase::Scene _SceneTag, const Tag& _ObjectTag, const float& _Scale)
	: GameObject(_SceneTag, _ObjectTag)
{

}

/*
@fn �h���N���X�̍X�V�֐����Ăэ��W�Ɉړ��ʂ𑫂�������
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void UIBase::UpdateGameObject(float _deltaTime)
{

}