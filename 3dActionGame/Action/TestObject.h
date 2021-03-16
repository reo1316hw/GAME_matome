#pragma once
#include "GameObject.h"

class SkeletalMeshComponent;

/*
���f���f�[�^��ǂݍ���ŃA�j���[�V�������s���Ă����N���X
�⏕�N���X�ō��Ɉړ��������L�[�{�[�h��A�������ƉE�Ɉړ�����e�X�gGameObject�N���X
*/
class TestObject :
    public GameObject
{
public:
    TestObject();
    ~TestObject();
    void UpdateGameObject(float _deltaTime)override;
    void GameObjectInput(const InputState& _keyState)override;

private:
    //3D���f���̕`����s���N���X
    SkeletalMeshComponent* skeltalMeshComponent;
};

