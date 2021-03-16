#include "TestObject.h"
#include "SkeletalMeshComponent.h"
#include "MeshComponent.h"
#include "MainCameraObject.h"
#include <string>
#include "Renderer.h"
#include "Skeleton.h"
#include "Animation.h"
#include "InputSystem.h"
#include "TestComponent.h"

TestObject::TestObject() :
	GameObject()
{
	//GameObject�����o�ϐ��̏�����
	tag = Tag::Other;
	SetScale(1.0f);
	SetPosition(Vector3(0, 0, 0));

	//�X�V�̓x�ɍ��Ɉړ�����R���|�[�l���g�𐶐� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	//new TestComponent(this);

	//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Skelton_King/skeleton_king_king.gpmesh"));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/Skelton_King/skeleton_king_king.gpskel"));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	const Animation* anim = RENDERER->GetAnimation("Assets/Model/Skelton_King/KingRun.gpanim");
	//anim�ϐ��𑬓x0.5f�ōĐ�
	skeltalMeshComponent->PlayAnimation(anim, 0.5f);

	//Z����270�x��]������
	float radian = Math::ToRadians(270);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

	//X����-90�x��]������
	radian = Math::ToRadians(-90);
	rot = this->GetRotation();
	inc = Quaternion(Vector3::UnitX, radian);
	target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

TestObject::~TestObject()
{
}

void TestObject::UpdateGameObject(float _deltaTime)
{
	//Vector3(-200, 140, -800)��������������position���ɂ₩�ɒǐՂ���B
	//mainCamera->SetViewMatrixLerpObject(Vector3(-200, 140, -800), position);
}

void TestObject::GameObjectInput(const InputState& _keyState)
{
	//�L�[�{�[�hA�����͂��ꂽ��-x�𑫂�
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
	{
		SetPosition(position + Vector3(-20, 0, 0));
	}

	//�L�[�{�[�hD�����͂��ꂽ��x�𑫂�
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
	{
		SetPosition(position + Vector3(20, 0, 0));
	}

	//�L�[�{�[�hW�����͂��ꂽ��z�𑫂�
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
	{
		SetPosition(position + Vector3(0, 0, 20));
	}

	//�L�[�{�[�hS�����͂��ꂽ��-z�𑫂�
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
	{
		SetPosition(position + Vector3(0, 0, -20));
	}
}
