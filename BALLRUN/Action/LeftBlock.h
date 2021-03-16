#pragma once
#include "GameObject.h"

class LeftBlock : public GameObject
{
public:
	LeftBlock(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag);
	~LeftBlock() {};

	void UpdateGameObject(float _deltaTime)override;
private:

	//���]������W
	Vector3 inversionPos;

	//�h��邩
	bool shakeFlag;
	//���]���邩
	bool reversFlag;

	//����(�i�s�x)
	float elapseTime;
	//�J�n�ƏI���̒l�̍���
	float differencePos;
	//�J�n�̒l
	float start;
	//Tween(�g�D�C�[��)�̍��v����
	const float totalTime = 1.0f;

	const float LEFT_SPEED = 20;
};