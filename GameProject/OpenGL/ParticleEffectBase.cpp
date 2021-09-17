/*
@file ParticleEffectBase.h
@brief ��莞�Ԃŏ�����A��ɃG�t�F�N�g�̊��N���X�Ƃ��Ďg�p�����N���X
*/

/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �G�t�F�N�g�̐����ꏊ
@param	_Vel �G�t�F�N�g�̑��x
@param	_LifeCount �G�t�F�N�g�̐�������
@param	_ParticleFileName �摜�ւ̃A�h���X
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
@param	_Scale �摜�̊g��T�C�Y
*/
ParticleEffectBase::ParticleEffectBase(const Vector3& _Pos, const Vector3& _Vel, const int& _LifeCount, const std::string& _ParticleFileName, const SceneBase::Scene _SceneTag, const Tag& _ObjectTag,const float& _Scale)
	: GameObject(_SceneTag,_ObjectTag)
	 ,mLifeCount(_LifeCount)
{
	mVelocity = _Vel;
	mParticle = new ParticleComponent(this);
	mParticle->SetTextureID(RENDERER->GetTexture(_ParticleFileName)->GetTextureID());
	mParticle->SetColor(Color::sWHITE);
	mParticle->SetScale(_Scale);
	SetPosition(_Pos);
}

/*
@fn		�h���N���X�̍X�V�֐����Ăэ��W�Ɉړ��ʂ𑫂�������
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void ParticleEffectBase::UpdateGameObject(float _deltaTime)
{
	LifeCountDown();
	SetPosition(mPosition + mVelocity);
}

/*
@fn �������Ԃ��J�E���g�_�E������֐��B�h���N���X�ōX�V�֐������肵���ꍇ�����ɒǉ����邱�ƁB
*/
void ParticleEffectBase::LifeCountDown()
{
	//�������Ԃ��[���ɂȂ�Ƃ��̃I�u�W�F�N�g���X�V�I������
	if (mLifeCount <= 0)
	{
		mParticle->SetVisible(false);
		SetState(State::Dead);
	}
	else
	{
		mParticle->SetVisible(true);
		mLifeCount--;
	}

}

/*
@param _flag ���]���s����
*/
void ParticleEffectBase::SetReverve(float _flag)
{
	mParticle->SetReverce(_flag);
}