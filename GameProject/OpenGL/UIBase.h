/*
@brief �v���v���Z�b�T
*/
#pragma once

class UIBase : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos UI�̐����ꏊ(�X�N���[�����W)
	@param	_UiFileName �摜�ւ̃A�h���X
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
	@param	_Scale �摜�̊g��T�C�Y
	*/
	UIBase(const Vector2& _Pos,const std::string& _UiFileName, const SceneBase::Scene _SceneTag, const Tag& _ObjectTag, const float& _Scale = 10);

	/*
	@fn	�f�X�g���N�^
	*/
	~UIBase() {};

	/*
	@fn �h���N���X�̍X�V�֐����Ăэ��W�Ɉړ��ʂ𑫂�������
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

protected:
	
	//UI�̕`��N���X
	UIComponent* mUI;
	//�v���C���[�̃|�C���^
	Player* mPlayer;
};
