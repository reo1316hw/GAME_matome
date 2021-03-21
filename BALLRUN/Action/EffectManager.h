#pragma once
#include "ParticleEffectBase.h"

class SandEffect;
class DeathEffect;
class ClearEffect;
class Player;

class EffectManager :
	public GameObject
{
public:
	EffectManager(GameObject* _owner, SceneBase::Scene _sceneTag , const Tag& _objectTag);
	~EffectManager() {};

	void UpdateGameObject(float _deltaTime)override;
	
private:
	GameObject*		 mOwner;
	ParticleState	 mState;
	Vector3			 mPrePos;
	SceneBase::Scene mSceneTag;
	Tag				 mTag;
	SandEffect*		 mSandEffect;
	DeathEffect*	 mDeathEffect;
	ClearEffect*	 mClearEffect;
	Player*			 mPlayer;

	int				 mFrameCount;
	int				 mScene;

	// Šp“x
	float			 mAngle;

	bool			 mClearEffectFlag;
	bool			 mDeathEffectFlag;
};

