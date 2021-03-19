#include "RightBlock.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Player.h"

RightBlock::RightBlock(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, objectTag)
	, elapseTime(0.0f)
	, differencePos(0.0f)
	, start(0.0f)
	, shakeFlag(false)
	, inversionPos(Vector3::Zero)
{
	//GameObject�����o�ϐ��̏�����
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	initPos = Vector3(_pos.x, _pos.y, _pos.z);
	endPos = Vector3(_pos.x + 600, _pos.y, _pos.z);
	inversionPos = Vector3(_pos.x + 60, _pos.y, _pos.z);

	//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	meshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_15.gpmesh"));

	// �����蔻��
	mesh = new Mesh;
	mesh = RENDERER->GetMesh("Assets/box_15.gpmesh");
	boxcollider = new BoxCollider(this, ColliderTag::rightBlockTag, GetOnCollisionFunc());
	boxcollider->SetObjectBox(mesh->GetBox());

	originalPosFlag = false;
}

void RightBlock::UpdateGameObject(float _deltaTime)
{
	Vector3 playerPos = Player::GetPos();
	//////////////////////////////////////
	//�\�m���쏈��

	if (playerPos.z >= position.z - 2040.0f)
	{
		shakeFlag = true;
	}

	if (shakeFlag)
	{
		if (position.x >= inversionPos.x)
		{
			reversFlag = true;
		}
		else if (position.x <= initPos.x)
		{
			reversFlag = false;
		}

		if (reversFlag == true)
		{
			/*Vector3 movePos = Vector3(position + Vector3(50, 0, 0));
			position = Vector3::Lerp(position,movePos,0.1f);*/

			velocity.x = -RIGHT_SPEED;
		}
		else if (reversFlag == false)
		{
			/*Vector3 movePos2 = Vector3(position + Vector3(-50, 0, 0));
			position = Vector3::Lerp(position, movePos2, 0.1f);*/

			velocity.x = RIGHT_SPEED;
		}
	}
	/////////////////////////////////////////

	if (playerPos.z >= position.z - 1800.0f)
	{
		shakeFlag = false;
		elapseTime += _deltaTime;
		differencePos = endPos.x - initPos.x;
		velocity.x = Quartic::EaseIn(elapseTime, start , differencePos, totalTime) * 0.02f;
		//velocity.x = RIGHT_SPEED;
	}

	if (initPos.x < position.x)
	{
		originalPosFlag = true;
	}

	if (position.x >= endPos.x)
	{
		velocity.x = 0;
	}

	if (Player::GetDeathFlag())
	{
		elapseTime = 0.0f;
		velocity.x = 0;
		originalPosFlag = false;
	}

	if (originalPosFlag)
	{
		if (Player::GetRespawnFlag())
		{
			elapseTime = 0.0f;
			velocity.x = 0;
			position.x = initPos.x;
			originalPosFlag = false;
		}
	}

	aabb = boxcollider->GetWorldBox();

	// ��ɍ��W�ɑ��x�𑫂�
	position += velocity;

	SetPosition(position);
}