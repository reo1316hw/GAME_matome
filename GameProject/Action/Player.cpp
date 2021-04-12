/*
@brief	インクルード
*/
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

Vector3 Player::mSendPos = Vector3::Zero;
bool	Player::mSendClearFlag = false;
bool	Player::mSendDeathFlag = false;
bool    Player::mSendRespawnFlag = false;
int     Player::mSendLife = 0;

/*
@fn		コンストラクタ
@param	_pos プレイヤーの座標
@param	_size プレイヤーのサイズ
@param	_objectTag プレイヤーのタグ
@param	_sceneTag シーンのタグ
*/
Player::Player(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
	, mPlayerSphere(Vector3::Zero,0.0f)
	, mVisibleFrameCount(0)
	, mLife(0)
	, mAngle(0.0f)
	, mScene(SceneBase::other)
	, mDeathFlag(false)
	, mDamageFlag(false)
	, mStopFlag(false)
	, mClearFlag(false)
	, mJumpFlag(false)
	, mScaleFlag(false)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// 速度の値
	mMoveSpeed = PLAYER_SPEED;
	mGravity   = GRAVITY_ACCEL;
	mLife	  = PLAYER_LIFE;
	mRespawnState = RespawnState::respawnNone;

	//生成したPlayerの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);

	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Sphere.gpmesh"));

	mEffectManager = new EffectManager(this, _sceneTag, _objectTag);

	//プレイヤー自身の当たり判定
	mSelfSphereCollider = new SphereCollider(this, ColliderTag::playerTag, GetOnCollisionFunc());
	Sphere sphere = { Vector3::Zero,30.0f };
	mSelfSphereCollider->SetObjectSphere(sphere);

	mLateralMoveVelocity = Vector3::Zero;
}

/*
@fn		プレイヤーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void Player::UpdateGameObject(float _deltaTime)
{
	mMainCamera->SetViewMatrixLerpObject(Vector3(0, 500, -550), mPosition);

	mScene = SceneBase::GetScene();

	if (mClearFlag)
	{
		SetState(State::Dead);
	}

	if (mPosition.y <= -700)
	{
		mPosition.y = -699.0f;
		mDamageFlag = true;
	}

	if (mDamageFlag)
	{
		mLife -= 1;
		mRespawnFlag = true;
		mDamageFlag  = false;
	}

	if (mScene == SceneBase::tutorial)
	{
		mMoveSpeed = TUTORIAL_MOVE_SPEED;

		if (mJumpFlag)
		{
			mLateralMoveVelocity = Vector3::Zero;
			mVelocity.y = 50.0f;
			mScaleFlag = true;
			mJumpFlag = false;
		}

		if (mRespawnState == RespawnState::respawnNone)
		{
			if (mRespawnFlag)
			{
				if (mLife >= 1)
				{
					mPosition = Vector3(800.0f, 500.0f, -99800.0f);
				}
			}
		}

		if (mPosition.z >= -75700)
		{
			mClearFlag = true;
		}
	}

	if (mScene == SceneBase::stage01)
	{
		if (mJumpFlag)
		{
			mLateralMoveVelocity = Vector3::Zero;
			mVelocity.y = 40.0f;
			mScaleFlag = true;
			mJumpFlag = false;
		}

		switch (mRespawnState)
		{
		case RespawnState::respawnNone:
			if (mRespawnFlag)
			{
				if (mLife >= 1)
				{
					mPosition = Vector3(800.0f, 500.0f, -99800.0f);
				}
			}
			break;
		case RespawnState::respawnComplete01:

			if (mRespawnFlag)
			{
				if (mLife >= 1)
				{
					mPosition = Vector3(800.0f, 500.0f, -81000.0f);
				}
			}

			break;
		case RespawnState::respawnComplete02:

			if (mRespawnFlag)
			{
				if (mLife >= 1)
				{
					mPosition = Vector3(800.0f, 500.0f, -56500.0f);
				}
			}

			break;
		case RespawnState::respawnComplete03:

			if (mRespawnFlag)
			{
				if (mLife >= 1)
				{
					mPosition = Vector3(1100.0f, 500.0f, -37500.0f);
				}
			}

			break;
		}

		if (mPosition.z >= -8900)
		{
			mClearFlag = true;
		}
	}

	if (mScene == SceneBase::stage02)
	{
		if (mJumpFlag)
		{
			mLateralMoveVelocity = Vector3::Zero;
			mVelocity.y = 40.0f;
			mScaleFlag = true;
			mJumpFlag = false;
		}

		switch (mRespawnState)
		{
		case RespawnState::respawnNone:
			if (mRespawnFlag)
			{
				if (mLife >= 1)
				{
					mPosition = Vector3(800.0f, 500.0f, -99800.0f);
				}
			}
			break;
		case RespawnState::respawnComplete01:

			if (mRespawnFlag)
			{
				if (mLife >= 1)
				{
					mPosition = Vector3(800.0f, 500.0f, -83000.0f);
				}
			}

			break;
		case RespawnState::respawnComplete02:

			if (mRespawnFlag)
			{
				if (mLife >= 1)
				{
					mPosition = Vector3(800.0f, 500.0f, -61500.0f);
				}
			}

			break;
		case RespawnState::respawnComplete03:

			if (mRespawnFlag)
			{
				if (mLife >= 1)
				{
					mPosition = Vector3(800.0f, 500.0f, -30000.0f);
				}
			}

			break;
		}

		if (mPosition.z >= -2100)
		{
			mClearFlag = true;
		}
	}

	if (mRespawnFlag)
	{
		mLateralMoveVelocity = Vector3::Zero;

		if (mLife >= 1)
		{
			mStopFlag = true;
		}
	}

	if (mStopFlag)
	{
		mAngle = 0.0f;

		mVisibleFrameCount++;
		if (mVisibleFrameCount % 10 == 0)
		{
			mMeshComponent->SetVisible(false);
		}

		if (mVisibleFrameCount % 10 == 5)
		{
			mMeshComponent->SetVisible(true);
		}

		mVelocity = Vector3::Zero;
		if (mVisibleFrameCount >= 40)
		{
			mVisibleFrameCount = 0;
			mVelocity.z = mMoveSpeed;
			mVelocity.y = mMoveSpeed;
			mStopFlag = false;

			mMeshComponent->SetVisible(true);
		}
	}
	
	if (mLife <= 0)
	{
		mDeathFlag = true;
		SetState(State::Dead);
	}

	if (mScaleFlag)
	{
		mScale.y = 1.2f + (mPosition.y - 120.0f) * 0.0015f;
		mScale.z = 1.2f + (mPosition.y - 120.0f) * 0.0015f;
	}
	if (mPosition.y <= 120.0f && mVelocity.y <= 0.0f)
	{
		mScaleFlag = false;
		mScale.x = 1.2f;
		mScale.y = 1.2f;
		mScale.z = 1.2f;
	}

	if (mPosition.y >= 200)
	{
		if (mStopFlag == false)
		{
			mAngle = 2.0f;
		}
	}
	else
	{
		//回転処理
		mAngle = 10.0f;
	}

	float radian = Math::ToRadians(mAngle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitX, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
	

	// 常に座標に速度を足す
	mPosition += mVelocity + mLateralMoveVelocity;

	mVelocity.y -= mGravity;

	mSendPos			= mPosition;
	mSendClearFlag		= mClearFlag;
	mSendDeathFlag		= mDeathFlag;
	mSendRespawnFlag	= mRespawnFlag;
	mSendLife			= mLife;

	mRespawnFlag = false;

	// 座標をセット
	SetPosition(mPosition);
}

/*
@fn		入力を引数で受け取る更新関数
@brief	基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
@param	_keyState 各入力機器の入力状態
@brief	キーボード、マウス、コントローラー
*/
void Player::GameObjectInput(const InputState& _keyState)
{
	// 常に前に進む
	if (mStopFlag == false)
	{
		//mVelocity.z = mMoveSpeed;

		// コントローラーの十字上もしくはキーボード、Wが入力されたらzを足す
		if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 1 ||
			_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
		{
			mVelocity.z = mMoveSpeed;
		}
		// コントローラーの十字下もしくは、キーボードSが入力されたら-zを足す
		else if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1 ||
				 _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
		{
			mVelocity.z = -mMoveSpeed;
		}
		// コントローラーの十字上かコントローラーの十字下かキーボードWかキーボードSが入力されなかったら速度を0にする
		else if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 0  ||
				 _keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 0  ||
				 _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) == 0 ||
				 _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) == 0)
		{
			mVelocity.z *= 0;
		}

		 //コントローラーの十字左もしくは、キーボードAが入力されたら-xを足す
		if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 ||
			_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
		{
			mVelocity.x = -mMoveSpeed;
		}
		// コントローラーの十字右もしくは、キーボードDが入力されたらxを足す
		else if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 ||
			_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
		{
			mVelocity.x = mMoveSpeed;
		}

		// コントローラーの十字左かコントローラーの十字右かキーボードAかキーボードDが入力されなかったら速度を0にする
		else if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 0 ||
			_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 0 ||
			_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) == 0 ||
			_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) == 0)
		{
			mVelocity.x *= 0;
		}

		/*if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_B) == 1  ||
			_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_SPACE) == 1)
		{
			mVelocity.y = 40.0f;
		}*/
	}
}

/*
@fn		プレイヤーがヒットした時の処理
@param	_hitObject ヒットした対象のゲームオブジェクトのアドレス
*/
void Player::OnCollision(const GameObject& _hitObject)
{
	// 重力を消す
	mVelocity.y = 0;

	mTag = _hitObject.GetTag();

	if (mTag == block ||
		mTag == verticalBlock ||
		mTag == rightBlock ||
		mTag == leftBlock ||
		mTag == rightOneBlock_02 ||
		mTag == leftOneBlock_02 ||
		mTag == aerialBlock ||
		mTag == upBlock)
	{
		mDamageFlag = true;
	}

	if (mTag == lateralMoveGround)
	{
		mLateralMoveVelocity = mLateral->GetVelocity();
	}
	else
	{
		mLateralMoveVelocity = Vector3::Zero;
	}

	if (mTag == jump)
	{
		mJumpFlag = true;
	}

	if (mTag == respawn01)
	{
		mRespawnState = RespawnState::respawnComplete01;
	}
	if (mTag == respawn02)
	{
		mRespawnState = RespawnState::respawnComplete02;
	}
	if (mTag == respawn03)
	{
		mRespawnState = RespawnState::respawnComplete03;
	}
}
