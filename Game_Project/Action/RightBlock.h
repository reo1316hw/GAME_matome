#pragma once
#include "GameObject.h"

class RightBlock : public GameObject
{
public:
	RightBlock(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~RightBlock() {};

	void UpdateGameObject(float _deltaTime)override;
private:

	Vector3 mInversionPos;
	//�h��邩
	bool mShakeFlag;
	//���]���邩
	bool mReversFlag;

	//����(�i�s�x)
	float mElapseTime;
	//�J�n�ƏI���̒l�̍���
	float mDifferencePos;
	//�J�n�̒l
	float mStart;
	//Tween(�g�D�C�[��)�̍��v����
	const float TOTAL_TIME = 1.0f;

	const float RIGHT_SPEED = 20.0f;
};