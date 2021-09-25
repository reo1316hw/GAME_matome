/*
@brief �v���v���Z�b�T
*/
#pragma once

class GoalLine : public ParticleEffectBase
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_Pos �S�[�����C���̍��W
	@param	_Vel �S�[�����C���̑��x
	@param	_TextureName �e�N�X�`���f�[�^�̃p�X
	@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
	@param	_SceneTag �V�[���̃^�O
    @param	_playerPtr �v���C���[�̃|�C���^
	*/
	GoalLine(const Vector3& _Pos, const Vector3& _Vel,const std::string& _TextureName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
	@fn	�f�X�g���N�^
	*/
	~GoalLine() {};

	/*
	@fn		�S�[�����C���̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	Player* mPlayer;
};

