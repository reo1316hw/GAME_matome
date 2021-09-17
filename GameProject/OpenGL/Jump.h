/*
@brief �v���v���Z�b�T
*/
#pragma once

class Jump : public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �W�����v���̍��W
	@param	_Size �W�����v���̃T�C�Y
	@param	_ObjectTag �W�����v���̃^�O
	@param	_SceneTag �V�[���̃^�O
	*/
	Jump(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~Jump() {};

	/*
	@fn		�W�����v���̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn		�W�����v�����q�b�g�������̏���
	@param	_HitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
	*/
	void OnCollision(const GameObject& _HitObject)override;

private:

	// �v���C���[�̃|�C���^
	Player* mPlayer;

	//�p�x
	float degree;
};