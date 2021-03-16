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
	//GameObjectメンバ変数の初期化
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// 速度の値
	moveSpeed = PLAYER_SPEED;
	gravity   = GRAVITY_ACCEL;
	life	  = PLAYER_LIFE;
	respawnState = RespawnState::respawnNone;

	//更新の度に左に移動するコンポーネントを生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	/*new TestComponent(this);*/

	//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	meshComponent = new MeshComponent(this);

	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Sphere.gpmesh"));

	effectManager = new EffectManager(this, _sceneTag, objectTag);


	//プレイヤー自身の当たり判定
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
		//回転処理
		angle = 10.0f;
	}

	float radian = Math::ToRadians(angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitX, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
	

	// 常に座標に速度を足す
	position += velocity + moveVelocity;

	velocity.y -= gravity;

	sendPos = position;
	sendClearFlag = clearFlag;
	sendDeathFlag = deathFlag;
	sendRespawnFlag = respawnFlag;
	sendLife = life;

	respawnFlag = false;

	// 座標をセット
	SetPosition(position);
}

void Player::GameObjectInput(const InputState& _keyState)
{
	// 常に前に進む
	if (stopFlag == false)
	{
		velocity.z = moveSpeed;

		//// コントローラーの十字上もしくはキーボード、Wが入力されたらzを足す
		//if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 1 || 
		//	_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
		//{
		//	velocity.z = moveSpeed;
		//}
		//// コントローラーの十字下もしくは、キーボードSが入力されたら-zを足す
		//else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1 ||
		//		 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
		//{
		//	velocity.z = -moveSpeed;
		//}
		//// コントローラーの十字上かコントローラーの十字下かキーボードWかキーボードSが入力されなかったら速度を0にする
		//else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 0  ||
		//		 _keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 0  ||
		//		 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) == 0 ||
		//		 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) == 0)
		//{
		//	velocity.z *= 0;
		//}

		 //コントローラーの十字左もしくは、キーボードAが入力されたら-xを足す
		if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 ||
			_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
		{
			velocity.x = -moveSpeed;
		}
		// コントローラーの十字右もしくは、キーボードDが入力されたらxを足す
		else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 ||
			_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
		{
			velocity.x = moveSpeed;
		}

		// コントローラーの十字左かコントローラーの十字右かキーボードAかキーボードDが入力されなかったら速度を0にする
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
	// 重力を消す
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
