/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �S�[�����C���̍��W
@param	_Vel �S�[�����C���̑��x
@param	_TextureName �e�N�X�`���f�[�^�̃p�X
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
@param	_playerPtr �v���C���[�̃|�C���^
*/
GoalLine::GoalLine(const Vector3& _Pos, const Vector3& _Vel, const std::string& _TextureName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
	: ParticleEffectBase(_Pos, _Vel, 0, _TextureName, _SceneTag, _ObjectTag)
{
	mInitPos = _Pos;
	mPosition = _Pos;
	mVelocity = _Vel;
	mScale = 100.0f;
	mAlpha = 0.5f;
	mParticle->SetScale(mScale);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Color::sWHITE);

	mPlayer = _playerPtr;
}

void GoalLine::UpdateGameObject(float _deltaTime)
{
	if (mPlayer->GetGoalProductionFlag())
	{
		mVelocity *= 1.05f;
		mPosition += mVelocity;
	}
	
	SetPosition(mPosition);
}
