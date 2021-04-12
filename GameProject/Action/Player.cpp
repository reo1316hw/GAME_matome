/*
@brief	�C���N���[�h
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
@fn		�R���X�g���N�^
@param	_pos �v���C���[�̍��W
@param	_size �v���C���[�̃T�C�Y
@param	_objectTag �v���C���[�̃^�O
@param	_sceneTag �V�[���̃^�O
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
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// ���x�̒l
	mMoveSpeed = PLAYER_SPEED;
	mGravity   = GRAVITY_ACCEL;
	mLife	  = PLAYER_LIFE;
	mRespawnState = RespawnState::respawnNone;

	//��������Player�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);

	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Sphere.gpmesh"));

	mEffectManager = new EffectManager(this, _sceneTag, _objectTag);

	//�v���C���[���g�̓����蔻��
	mSelfSphereCollider = new SphereCollider(this, ColliderTag::playerTag, GetOnCollisionFunc());
	Sphere sphere = { Vector3::Zero,30.0f };
	mSelfSphereCollider->SetObjectSphere(sphere);

	mLateralMoveVelocity = Vector3::Zero;
}

/*
@fn		�v���C���[�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
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
		//��]����
		mAngle = 10.0f;
	}

	float radian = Math::ToRadians(mAngle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitX, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
	

	// ��ɍ��W�ɑ��x�𑫂�
	mPosition += mVelocity + mLateralMoveVelocity;

	mVelocity.y -= mGravity;

	mSendPos			= mPosition;
	mSendClearFlag		= mClearFlag;
	mSendDeathFlag		= mDeathFlag;
	mSendRespawnFlag	= mRespawnFlag;
	mSendLife			= mLife;

	mRespawnFlag = false;

	// ���W���Z�b�g
	SetPosition(mPosition);
}

/*
@fn		���͂������Ŏ󂯎��X�V�֐�
@brief	��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
@param	_keyState �e���͋@��̓��͏��
@brief	�L�[�{�[�h�A�}�E�X�A�R���g���[���[
*/
void Player::GameObjectInput(const InputState& _keyState)
{
	// ��ɑO�ɐi��
	if (mStopFlag == false)
	{
		//mVelocity.z = mMoveSpeed;

		// �R���g���[���[�̏\����������̓L�[�{�[�h�AW�����͂��ꂽ��z�𑫂�
		if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 1 ||
			_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
		{
			mVelocity.z = mMoveSpeed;
		}
		// �R���g���[���[�̏\�����������́A�L�[�{�[�hS�����͂��ꂽ��-z�𑫂�
		else if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1 ||
				 _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
		{
			mVelocity.z = -mMoveSpeed;
		}
		// �R���g���[���[�̏\���ォ�R���g���[���[�̏\�������L�[�{�[�hW���L�[�{�[�hS�����͂���Ȃ������瑬�x��0�ɂ���
		else if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 0  ||
				 _keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 0  ||
				 _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) == 0 ||
				 _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) == 0)
		{
			mVelocity.z *= 0;
		}

		 //�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ��-x�𑫂�
		if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 ||
			_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
		{
			mVelocity.x = -mMoveSpeed;
		}
		// �R���g���[���[�̏\���E�������́A�L�[�{�[�hD�����͂��ꂽ��x�𑫂�
		else if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 ||
			_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
		{
			mVelocity.x = mMoveSpeed;
		}

		// �R���g���[���[�̏\�������R���g���[���[�̏\���E���L�[�{�[�hA���L�[�{�[�hD�����͂���Ȃ������瑬�x��0�ɂ���
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
@fn		�v���C���[���q�b�g�������̏���
@param	_hitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
*/
void Player::OnCollision(const GameObject& _hitObject)
{
	// �d�͂�����
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
