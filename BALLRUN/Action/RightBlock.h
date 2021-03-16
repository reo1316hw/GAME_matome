#pragma once
#include "GameObject.h"

class RightBlock : public GameObject
{
public:
	RightBlock(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag);
	~RightBlock() {};

	void UpdateGameObject(float _deltaTime)override;
private:

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

	const float RIGHT_SPEED = 20;
};