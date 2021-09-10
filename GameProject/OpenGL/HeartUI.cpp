/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_pos �v���C���[�̗̑�UI�̐����ꏊ(�X�N���[�����W)
@param	_objectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_sceneTag �V�[���̃^�O
@param _playerPtr �v���C���[�̃|�C���^
*/
HeartUI::HeartUI(const Vector2& _pos, const Tag& _objectTag, SceneBase::Scene _sceneTag, Player* _playerPtr)
	:UIBase(_pos, "Assets/heart02.png", _sceneTag, _objectTag)
{
	mUI = new UIComponent(this);
	mUI->SetTexture(RENDERER->GetTexture("Assets/heart.png"));

	mPosition = Vector3(_pos.x, _pos.y, 0.0f);

	mPlayer = _playerPtr;
}

/*
@fn		�v���C���[�̗̑�UI�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void HeartUI::UpdateGameObject(float _deltaTime)
{
	if (mPlayer->GetLife() == 2)
	{
		if (mUI->GetUIid() == 2 || mUI->GetUIid() == 5 || mUI->GetUIid() == 8)
		{
			mUI->SetVisible(false);

		}
	}

	if (mPlayer->GetLife() == 1)
	{
		if (mUI->GetUIid() == 1 || mUI->GetUIid() == 4 || mUI->GetUIid() == 7)
		{
			mUI->SetVisible(false);

		}
	}

	if (mPlayer->GetLife() == 0)
	{
		if (mUI->GetUIid() == 0 || mUI->GetUIid() == 3 || mUI->GetUIid() == 6)
		{
			mUI->SetVisible(false);
		}
	}
}
