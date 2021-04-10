/*
@brief	�C���N���[�h
*/
#include "AerialBlock.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"

/*
@fn		�R���X�g���N�^
@param	_pos �Q�[���I�u�W�F�N�g�̍��W
@param	_size �Q�[���I�u�W�F�N�g�̃T�C�Y
@param	_objectTag �Q�[���I�u�W�F�N�g�̃^�O
@param	_sceneTag �V�[���̃^�O
*/
AerialBlock::AerialBlock(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//��������AerialBlock�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box_15.gpmesh"));

	//�����蔻��
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh("Assets/box_15.gpmesh");
	mBoxcollider = new BoxCollider(this, ColliderTag::aerialBlockTag, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());
}