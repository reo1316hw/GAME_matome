/*
@brief �C���N���[�h
*/
#include "pch.h"

#include "CheckpointEffectManager.h"
#include "SandEffectManager.h"
#include "ClearEffectManager.h"
#include "DeathEffectManager.h"

/*
@fn		�R���X�g���N�^
@param	_pos �v���C���[�̍��W
@param	_size �v���C���[�̃T�C�Y
@param	_objectTag �v���C���[�̃^�O
@param	_sceneTag �V�[���̃^�O
*/
Player::Player(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
	, mPlayerSphere(Vector3::Zero,0.0f)
	, mVisibleFrameCount(0)
	, mLife(0)
	, mCheckpointEffectCount(0)
	, mAngle(0.0f)
	, mScene(SceneBase::other)
	, mDeathFlag(false)
	, mDamageFlag(false)
	, mStopFlag(false)
	, mClearFlag(false)
	, mJumpFlag(false)
	, mScaleFlag(false)
	, mGroundFlag(false)
	, mCollisionFlag(true)
	, mCheckpointFlag(false)
	, mRespawnFlag(false)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);
	mInitPos = _pos;
	mRespawnPos = _pos;

	mScene = _sceneTag;

	// ���x�̒l
	mMoveSpeed = PLAYER_CONSTANT_SPEED;
	mGravity   = GRAVITY_ACCEL;
	mLife	  = PLAYER_LIFE;

	//��������Player�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);

	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));

	//�G�t�F�N�g
	mSandEffectManager = new SandEffectManager(this, _objectTag, _sceneTag);
	mCheckpointEffectManager = new CheckpointEffectManager(_objectTag, _sceneTag, this);
	mClearEffectManager = new ClearEffectManager(_objectTag, _sceneTag, this);
	mDeathEffectManager = new DeathEffectManager(_objectTag, _sceneTag , this);

	//�v���C���[���g�̓����蔻��
	mSelfSphereCollider = new SphereCollider(this, ColliderTag::playerTag, GetOnCollisionFunc());
	Sphere sphere = { Vector3::Zero,30.0f };
	mSelfSphereCollider->SetObjectSphere(sphere);

	mLateralMoveVelocity = Vector3::Zero;
	mButtonFlag = false;
}

/*
@fn		�v���C���[�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void Player::UpdateGameObject(float _deltaTime)
{
	//�v���C���[�̎΂ߌ��ɃJ�������Z�b�g
	mMainCamera->SetViewMatrixLerpObject(Vector3(0, 500, -550), mPosition);

	//�X�e�[�W�N���A������v���C���[�̍X�V���~�߂�
	if (mClearFlag)
	{
		SetState(State::Dead);
	}

	//�v���C���[��������̍��W�܂ŗ�������_���[�W���󂯂�
	if (mPosition.y <= -700.0f)
	{
		mPosition.y = -699.0f;
		mDamageFlag = true;
	}

	//�_���[�W���󂯂���̗͂����炷
	if (mDamageFlag)
	{
		mLife -= 1;
		mRespawnFlag = true;
		mDamageFlag = false;
	}

	//�S�X�e�[�W���ʂ̃��X�|�[������
	if (mRespawnFlag)
	{
		mLateralMoveVelocity = Vector3::Zero;
		mCollisionFlag = true;

		if (mLife >= 1)
		{
			mPosition = mRespawnPos;
			mStopFlag = true;
		}
	}

	//�`���[�g���A��
	if (mScene == SceneBase::tutorial)
	{
		//�`���[�g���A�����̑O���ړ����x
		mMoveSpeed = TUTORIAL_MOVE_SPEED;
		//�`���[�g���A�����̃W�����v��
		if (mJumpFlag)
		{
			mLateralMoveVelocity = Vector3::Zero;
			mVelocity.y = TUTORIAL_JUMP_SPEED;
			mScaleFlag = true;
			mJumpFlag = false;
		}

		//�`���[�g���A�����̃S�[���̍��W
		if (mPosition.z >= -75700)
		{
			mClearFlag = true;
		}
	}

	//�X�e�[�W01
	if (mScene == SceneBase::stage01)
	{
		//�X�e�[�W01�̃W�����v��
		if (mJumpFlag)
		{
			mLateralMoveVelocity = Vector3::Zero;
			mVelocity.y = JUMP_SPEED;
			mScaleFlag = true;
			mJumpFlag = false;
		}

		//�X�e�[�W01�̃S�[�����W
		if (mPosition.z >= -8900)
		{
			mClearFlag = true;
		}
	}

	//�X�e�[�W02
	if (mScene == SceneBase::stage02)
	{
		//�X�e�[�W02�̃W�����v��
		if (mJumpFlag)
		{
			mLateralMoveVelocity = Vector3::Zero;
			mVelocity.y = JUMP_SPEED;
			mScaleFlag = true;
			mJumpFlag = false;
		}

		//�X�e�[�W02�̃S�[���̍��W
		if (mPosition.z >= -2100)
		{
			mClearFlag = true;
		}
	}

	//���X�|�[����̑ҋ@���Ԓ�����
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
	
	//�̗�0�ɂȂ������̏���
	if (mLife <= 0)
	{
		mDeathFlag = true;
		SetState(State::Dead);
	}

	///////////////////////////////////////////////////////
	//�X�P�[���k������
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
	///////////////////////////////////////////////////////

	//�W�����v�����Ƃ��ɉ�]��x�����鏈��
	if (mPosition.y >= 200)
	{
		if (mStopFlag == false)
		{
			mAngle = 2.0f;
		}
	}
	else
	{
		mAngle = 10.0f;
	}

	//��]����
	float radian = Math::ToRadians(mAngle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitX, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
	
	//�E�ړ��̍ő呬�x
	if (mVelocity.x >= PLAYER_MAX_SPEED)
	{
		mVelocity.x = PLAYER_MAX_SPEED;
	}
	//���ړ��̍ő呬�x
	if (mVelocity.x <= -PLAYER_MAX_SPEED)
	{
		mVelocity.x = -PLAYER_MAX_SPEED;
	}

	// ��ɑO�ɐi��
	if (mStopFlag == false)
	{
		mVelocity.z = mMoveSpeed;
	}

	//�{�^���������Ă��Ȃ��Ƃ��̌�������
	if (mButtonFlag == false)
	{
		//���x��0���傫�������ꍇ�ɉE�Ɍ���
		if (mVelocity.x > 0.0f)
		{
			mVelocity.x += -PLAYER_SPEED_DOWN;
		}
		//���x��0��菬���������ꍇ�ɍ��Ɍ���
		else if (mVelocity.x < 0.0f)
		{
			mVelocity.x += PLAYER_SPEED_DOWN;
		}
		
		//���x�������x�̒l�ƈꏏ�ɂȂ����瑬�x��0�ɌŒ肷��
		if (mVelocity.x <= PLAYER_SPEED_DOWN && mVelocity.x > 0.0f ||
			mVelocity.x >= -PLAYER_SPEED_DOWN && mVelocity.x < 0.0f)
		{
			mVelocity.x = 0.0f;
		}

	}

	//�ڒn���Ă��Ȃ������X�|�[�����̑ҋ@���Ԃ���Ȃ����ɏd�͏������s��
	if (mGroundFlag == false && mStopFlag == false)
	{
		mVelocity.y -= mGravity;
	}

	//�v���C���[��������̍��W�܂ŗ������瓖���蔻��𖳌��ɂ���
	if (mPosition.y < 30.0f)
	{
		mCollisionFlag = false;
	}

	//�`�F�b�N�|�C���g�G�t�F�N�g������̐������Ԃ�1�ɂȂ�����`�F�b�N�|�C���g�G�t�F�N�g�𔭐������Ȃ��悤�ɂ���
	if (mCheckpointEffectCount == 1)
	{
		mCheckpointFlag = false;
		mCheckpointEffectCount = 0;
	}

	//�`�F�b�N�|�C���g��ʉ߂�����`�F�b�N�|�C���g�G�t�F�N�g������̐������Ԃ��J�E���g����
	if (mCheckpointFlag)
	{
		mCheckpointEffectCount++;
	}

	// ��ɍ��W�ɑ��x�𑫂�
 	mPosition += mVelocity + mLateralMoveVelocity;

	// ���̃N���X�Ŏg�p���邽�߂Ƀ��X�|�[���t���O��ۑ����Ă���
	mSaveRespawnFlag = mRespawnFlag;

	mRespawnFlag = false;
	mGroundFlag = false;

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
	 //�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ��-x�𑫂�
	if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
	{
		mVelocity.x += -PLAYER_SPEED_UP;
	}
	// �R���g���[���[�̏\���E�������́A�L�[�{�[�hD�����͂��ꂽ��x�𑫂�
	else if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
	{
		mVelocity.x += PLAYER_SPEED_UP;
	}

	// �R���g���[���[�̏\�������R���g���[���[�̏\���E���L�[�{�[�hA���L�[�{�[�hD�����͂���Ȃ�������mButtonFlag��false�ɂ���
	else if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 0 ||
		_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 0 ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) == 0 ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) == 0)
	{
		mButtonFlag = false;
	}
}

/*
@fn		�v���C���[���q�b�g�������̏���
@param	_hitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
*/
void Player::OnCollision(const GameObject& _hitObject)
{
	if (mCollisionFlag)
	{
		//�q�b�g�����I�u�W�F�N�g�̃^�O���擾
		mTag = _hitObject.GetTag();

		//�W�����v����
		if (mTag == jump)
		{
			mJumpFlag = true;
		}

		//�`�F�b�N�|�C���g�ʉߔ���
		if (mTag == checkpoint)
		{
			mCheckpointFlag = true;
			mRespawnPos = _hitObject.GetPosition();
		}

		//�_���[�W����
		if (mTag == block ||
			mTag == verticalBlock ||
			mTag == rightBlock ||
			mTag == leftBlock ||
			mTag == rightOneMoveBlock ||
			mTag == leftOneMoveBlock ||
			mTag == aerialBlock ||
			mTag == upBlock)
		{
			mDamageFlag = true;
		}

		//�ڒn����
		if (mTag == ground ||
			mTag == glass ||
			mTag == verticalMoveGround ||
			mTag == rightGround ||
			mTag == leftGround ||
			mTag == lateralMoveGround ||
			mTag == jump ||
			mTag == downBlock)
		{
			//�d�͂�����
			mVelocity.y = 0;
			mGroundFlag = true;
		}

		//���ړ����̔���
		if (mTag == lateralMoveGround)
		{
			//�d�͂�����
			mVelocity.y = 0;
			//���ړ����̑��x���擾
			mLateralMoveVelocity = mLateral->GetVelocity();
		}
		else
		{
			mLateralMoveVelocity = Vector3::Zero;
		}
	}
}