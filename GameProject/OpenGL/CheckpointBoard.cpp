/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_pos �`�F�b�N�|�C���g�{�[�h�̍��W
@param	_vel �`�F�b�N�|�C���g�{�[�h�̑��x
@param	_objectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_sceneTag �V�[���̃^�O
*/
CheckpointBoard::CheckpointBoard(const Vector3& _pos, const Vector3& _vel, const std::string& _particleFileName ,const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	:ParticleEffectBase(_pos, _vel, 0, _particleFileName, _sceneTag, _objectTag)
	, mCehckpointBoardAABB(Vector3::Zero, Vector3::Zero)
{
	mInitPos = _pos;
	mScale = 3000.0f;
	mAlpha = 0.3f;
	mParticle->SetScale(mScale);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Vector3(1.0f, 1.0f, 1.0f));

	mCehckpointBoardAABB = {Vector3(-1500.0f,-1500.0f,-100.0f),Vector3(1500.0f,1500.0f,100.0f)};

	mBoxcollider = new BoxCollider(this, ColliderTag::checkpoint, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mCehckpointBoardAABB);
}