/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_pos �c�ړ����̐����p�l���̍��W
@param	_vel �c�ړ����̐����p�l���̑��x
@param	_objectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_sceneTag �V�[���̃^�O
*/
VerticalMoveGroundExplanationBoard::VerticalMoveGroundExplanationBoard(const Vector3& _pos, const Vector3& _velocity, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: ParticleEffectBase(_pos, _velocity, 0, "Assets/tutorial01.png", _sceneTag, _objectTag)
{
	mInitPos = _pos;
	mScale = 400.0f;
	mAlpha = 1.0f;
	mParticle->SetScale(mScale);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Vector3(1.0f, 1.0f, 1.0f));
}