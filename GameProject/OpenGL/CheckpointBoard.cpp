/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �`�F�b�N�|�C���g�{�[�h�̍��W
@param	_Vel �`�F�b�N�|�C���g�{�[�h�̑��x
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
*/
CheckpointBoard::CheckpointBoard(const Vector3& _Pos, const Vector3& _Vel, const std::string& _ParticleFileName ,const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:ParticleEffectBase(_Pos, _Vel, 0, _ParticleFileName, _SceneTag, _ObjectTag)
	, mCehckpointBoardAABB(Vector3::sZERO, Vector3::sZERO)
{
	mInitPos = _Pos;
	mScale = 3000.0f;
	mAlpha = 0.3f;
	mParticle->SetScale(mScale);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Color::sWHITE);

	mCehckpointBoardAABB = {Vector3(-1500.0f,-1500.0f,-100.0f),Vector3(1500.0f,1500.0f,100.0f)};

	mBoxcollider = new BoxCollider(this, ColliderTag::eCheckpoint, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mCehckpointBoardAABB);
}