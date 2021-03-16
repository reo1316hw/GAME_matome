#include "player.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "MainCameraObject.h"
#include "InputSystem.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "EffectManager.h"
#include "LateralMoveGround.h"

Vector3 Player::sendPos = Vector3::Zero;
bool	Player::sendClearFlag = false;
bool	Player::sendDeathFlag = false;
bool    Player::sendRespawnFlag = false;
int     Player::sendLife = 0;

Player::Player(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, objectTag)
	, playerSphere(Vector3::Zero,0.0f)
	, frameCount(0)
	, life(0)
	, angle(0.0f)
	, scene(SceneBase::other)
	, deathFlag(false)
	, damageFlag(false)
	, stopFlag(false)
	, clearFlag(false)
	, jumpFlag(false)
	, scaleFlag(false)
{
	//GameObject�����o�ϐ��̏�����
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// ���x�̒l
	moveSpeed = PLAYER_SPEED;
	gravity   = GRAVITY_ACCEL;
	life	  = PLAYER_LIFE;
	respawnState = RespawnState::respawnNone;

	//�X�V�̓x�ɍ��Ɉړ�����R���|�[�l���g�𐶐� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	/*new TestComponent(this);*/

	//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	meshComponent = new MeshComponent(this);

	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Sphere.gpmesh"));

	effectManager = new EffectManager(this, _sceneTag, objectTag);


	//�v���C���[���g�̓����蔻��
	selfSphereCollider = new SphereCollider(this, ColliderTag::playerTag, GetOnCollisionFunc());
	Sphere sphere = { Vector3::Zero,30.0f };
	selfSphereCollider->SetObjectSphere(sphere);

	moveVelocity = Vector3::Zero;
	JumpPos = Vector3(0, 120.0f, 0);
}

Player::~Player()
{
}

void Player::UpdateGameObject(float _deltaTime)
{
	mainCamera->SetViewMatrixLerpObject(Vector3(0, 500, -550), position);

	scene = SceneBase::GetScene();

	if (clearFlag)
	{
		SetState(State::Dead);
	}

	if (position.y <= -700)
	{
		position.y = -699.0f;
		damageFlag = true;
	}

	if (damageFlag)
	{
		life -= 1;
		respawnFlag = true;
		damageFlag  = false;
	}

	if (scene == SceneBase::tutorial)
	{
		moveSpeed = TUTORIAL_MOVE_SPEED;

		if (jumpFlag)
		{
			moveVelocity = Vector3::Zero;
			velocity.y = 50.0f;
			scaleFlag = true;
			jumpFlag = false;
		}

		if (respawnState == RespawnState::respawnNone)
		{
			if (respawnFlag)
			{
				if (life >= 1)
				{
					position = Vector3(800.0f, 500.0f, -99800.0f);
				}
			}
		}

		if (position.z >= -75700)
		{
			clearFlag = true;
		}
	}

	if (scene == SceneBase::stage01)
	{
		if (jumpFlag)
		{
			moveVelocity = Vector3::Zero;
			velocity.y = 40.0f;
			scaleFlag = true;
			jumpFlag = false;
		}

		switch (respawnState)
		{
		case RespawnState::respawnNone:
			if (respawnFlag)
			{
				if (life >= 1)
				{
					position = Vector3(800.0f, 500.0f, -99800.0f);
				}
			}
			break;
		case RespawnState::respawnComplete01:

			if (respawnFlag)
			{
				if (life >= 1)
				{
					position = Vector3(800.0f, 500.0f, -81000.0f);
				}
			}

			break;
		case RespawnState::respawnComplete02:

			if (respawnFlag)
			{
				if (life >= 1)
				{
					position = Vector3(800.0f, 500.0f, -56500.0f);
				}
			}

			break;
		case RespawnState::respawnComplete03:

			if (respawnFlag)
			{
				if (life >= 1)
				{
					position = Vector3(1100.0f, 500.0f, -37500.0f);
				}
			}

			break;
		}

		if (position.z >= -8900)
		{
			clearFlag = true;
		}
	}

	if (scene == SceneBase::stage02)
	{
		if (jumpFlag)
		{
			moveVelocity = Vector3::Zero;
			velocity.y = 40.0f;
			scaleFlag = true;
			jumpFlag = false;
		}

		switch (respawnState)
		{
		case RespawnState::respawnNone:
			if (respawnFlag)
			{
				if (life >= 1)
				{
					position = Vector3(800.0f, 500.0f, -99800.0f);
				}
			}
			break;
		case RespawnState::respawnComplete01:

			if (respawnFlag)
			{
				if (life >= 1)
				{
					position = Vector3(800.0f, 500.0f, -83000.0f);
				}
			}

			break;
		case RespawnState::respawnComplete02:

			if (respawnFlag)
			{
				if (life >= 1)
				{
					position = Vector3(800.0f, 500.0f, -61500.0f);
				}
			}

			break;
		case RespawnState::respawnComplete03:

			if (respawnFlag)
			{
				if (life >= 1)
				{
					position = Vector3(800.0f, 500.0f, -30000.0f);
				}
			}

			break;
		}

		if (position.z >= -2100)
		{
			clearFlag = true;
		}
	}

	if (respawnFlag)
	{
		moveVelocity = Vector3::Zero;

		if (life >= 1)
		{
			stopFlag = true;
		}
	}

	if (stopFlag)
	{
		angle = 0.0f;

		frameCount++;
		if (frameCount % 10 == 0)
		{
			meshComponent->SetVisible(false);
		}

		if (frameCount % 10 == 5)
		{
			meshComponent->SetVisible(true);
		}

		velocity = Vector3::Zero;
		if (frameCount >= 40)
		{
			frameCount = 0;
			velocity.z = moveSpeed;
			velocity.y = moveSpeed;
			stopFlag = false;

			meshComponent->SetVisible(true);
		}
	}
	
	if (life <= 0)
	{
		deathFlag = true;
		SetState(State::Dead);
	}

	if (scaleFlag)
	{
		scale.y = 1.2f + (position.y - 120.0f) * 0.0015f;
	}
	if (position.y <= 120.0f && velocity.y <= 0.0f)
	{
		scaleFlag = false;
		scale.x = 1.2f;
		scale.y = 1.2f;
		scale.z = 1.2f;
	}

	if (position.y >= 200)
	{
		if (stopFlag == false)
		{
			angle = 2.0f;
		}
	}
	else
	{
		//��]����
		angle = 10.0f;
	}

	float radian = Math::ToRadians(angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitX, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
	

	// ��ɍ��W�ɑ��x�𑫂�
	position += velocity + moveVelocity;

	velocity.y -= gravity;

	sendPos = position;
	sendClearFlag = clearFlag;
	sendDeathFlag = deathFlag;
	sendRespawnFlag = respawnFlag;
	sendLife = life;

	respawnFlag = false;

	// ���W���Z�b�g
	SetPosition(position);
}

void Player::GameObjectInput(const InputState& _keyState)
{
	// ��ɑO�ɐi��
	if (stopFlag == false)
	{
		velocity.z = moveSpeed;

		//// �R���g���[���[�̏\����������̓L�[�{�[�h�AW�����͂��ꂽ��z�𑫂�
		//if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 1 || 
		//	_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
		//{
		//	velocity.z = moveSpeed;
		//}
		//// �R���g���[���[�̏\�����������́A�L�[�{�[�hS�����͂��ꂽ��-z�𑫂�
		//else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1 ||
		//		 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
		//{
		//	velocity.z = -moveSpeed;
		//}
		//// �R���g���[���[�̏\���ォ�R���g���[���[�̏\�������L�[�{�[�hW���L�[�{�[�hS�����͂���Ȃ������瑬�x��0�ɂ���
		//else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 0  ||
		//		 _keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 0  ||
		//		 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) == 0 ||
		//		 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) == 0)
		//{
		//	velocity.z *= 0;
		//}

		 //�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ��-x�𑫂�
		if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 ||
			_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
		{
			velocity.x = -moveSpeed;
		}
		// �R���g���[���[�̏\���E�������́A�L�[�{�[�hD�����͂��ꂽ��x�𑫂�
		else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 ||
			_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
		{
			velocity.x = moveSpeed;
		}

		// �R���g���[���[�̏\�������R���g���[���[�̏\���E���L�[�{�[�hA���L�[�{�[�hD�����͂���Ȃ������瑬�x��0�ɂ���
		else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 0 ||
			_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 0 ||
			_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) == 0 ||
			_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D) == 0)
		{
			velocity.x *= 0;
		}

		/*if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_B) == 1  ||
			_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_SPACE) == 1)
		{
			velocity.y = 40.0f;
		}*/
	}
}
void Player::OnCollision(const GameObject& _hitObject)
{
	// �d�͂�����
	velocity.y = 0;

	tag = _hitObject.GetTag();

	if (tag == block ||
		tag == verticalBlock ||
		tag == rightBlock ||
		tag == leftBlock ||
		tag == rightOneBlock_02 ||
		tag == leftOneBlock_02 ||
		tag == aerialBlock ||
		tag == upBlock)
	{
		damageFlag = true;
	}

	if (tag == lateralMoveGround)
	{
		moveVelocity = lateral->GetVelocity();
	}
	else
	{
		moveVelocity = Vector3::Zero;
	}

	if (tag == jump)
	{
		jumpFlag = true;
	}

	if (tag == respawn01)
	{
		respawnState = RespawnState::respawnComplete01;
	}
	if (tag == respawn02)
	{
		respawnState = RespawnState::respawnComplete02;
	}
	if (tag == respawn03)
	{
		respawnState = RespawnState::respawnComplete03;
	}
}
