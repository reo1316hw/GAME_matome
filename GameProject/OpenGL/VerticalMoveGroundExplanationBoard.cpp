/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �c�ړ����̐����p�l���̍��W
@param	_Vel �c�ړ����̐����p�l���̑��x
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
*/
VerticalMoveGroundExplanationBoard::VerticalMoveGroundExplanationBoard(const Vector3& _Pos, const Vector3& _Vel, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: ParticleEffectBase(_Pos, _Vel, 0, "Assets/Texture/Board/TutorialVerticlMoveGround.png", _SceneTag, _ObjectTag)
{
	mInitPos = _Pos;
	mScale = 400.0f;
	mAlpha = 1.0f;
	mParticle->SetScale(mScale);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Color::sWHITE);
}