#include "ParticleEffectBase.h"
#include "Renderer.h"
#include "Texture.h"
#include "SceneBase.h"

ParticleEffectBase::ParticleEffectBase(const Vector3& _pos, const Vector3& _velocity, const int& _lifeCount, const std::string& _spriteFileName, SceneBase::Scene _sceneTag, const Tag& _objectTag,const float& _scale)
	: GameObject(_sceneTag,_objectTag)
	 ,mLifeCount(_lifeCount)
{
	mVelocity = _velocity;
	mParticle = new ParticleComponent(this);
	mParticle->SetTextureID(RENDERER->GetTexture(_spriteFileName)->GetTextureID());
	mParticle->SetColor(Vector3(1.0f, 1.0f, 1.0f));
	mParticle->SetScale(_scale);
	SetPosition(_pos);
}

ParticleEffectBase::~ParticleEffectBase()
{
}

void ParticleEffectBase::UpdateGameObject(float _deltaTime)
{
	UpdateParticleObject(_deltaTime);
	SetPosition(mPosition + mVelocity);
}

void ParticleEffectBase::UpdateParticleObject(float _deltaTime)
{
	LifeCountDown();
}

void ParticleEffectBase::LifeCountDown()
{
	//生存時間がゼロになるとこのオブジェクトを更新終了する
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

void ParticleEffectBase::SetReverve(float _flag)
{
	mParticle->SetReverce(_flag);

}