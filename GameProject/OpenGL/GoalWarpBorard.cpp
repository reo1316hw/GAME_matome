/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �S�[�����[�v�̍��W
@param	_Vel �S�[�����[�v�̑��x
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
*/
GoalWarpBorard::GoalWarpBorard(const Vector3& _Pos, const Vector3& _Vel, const std::string& _ParticleFileName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: ParticleEffectBase(_Pos, _Vel, 0, _ParticleFileName, _SceneTag, _ObjectTag)
	, mAngle(0.0f)
{
	mInitPos = _Pos;
	mScale = 1000.0f;
	mAlpha = 0.5f;
	mParticle->SetScale(mScale);
	mParticle->SetAlpha(mAlpha);
	mParticle->SetColor(Color::sWHITE);
}

/*
@fn		�S�[�����[�v�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void GoalWarpBorard::UpdateGameObject(float _deltaTime)
{
	mAngle += 10.0f;
	//��]����
	float radian = Math::ToRadians(mAngle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::sUNIT_Z, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}