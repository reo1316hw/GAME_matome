/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �S�[�����C���̐����ꏊ
@param	_Vel �S�[�����C���̑��x
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
*/
GoalLine::GoalLine(const Vector3& _Pos, const Vector3& _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: ParticleEffectBase(_Pos, _Vel, 0, "Assets/Goal.png", _SceneTag, _ObjectTag)
{
	mInitPos = _Pos;
	mScale = 1000.0f;
	mAlpha = 0.5f;
	mParticle->SetScale(mScale);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Color::sWHITE);
}