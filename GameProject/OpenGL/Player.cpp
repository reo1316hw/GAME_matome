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
@param	_Pos �v���C���[�̍��W
@param	_Size �v���C���[�̃T�C�Y
@param	_ObjectTag �v���C���[�̃^�O
@param	_SceneTag �V�[���̃^�O
*/
Player::Player(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_SceneTag, _ObjectTag)
	, mPlayerSphere(Vector3::sZERO,0.0f)
	, mVisibleFrameCount(0)
	, mLife(0)
	, mCheckpointEffectCount(0)
	, mAngle(0.0f)
	, MPlayerSpeedUp(10.0f)
	, MGroundYPos(120.0f)
	, mScene(SceneBase::Scene::eOtherScene)
	, mDeathFlag(false)
	, mDamageFlag(false)
	, mStopFlag(false)
	, mClearFlag(false)
	, mJumpFlag(false)
	, mScaleFlag(false)
	, mGroundFlag(false)
	, mCollisionFlag(true)
	, mEnableCheckpointFlag(false)
	, mRespawnFlag(false)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;
	mRespawnPos = _Pos;

	mScene = _SceneTag;

	// ���x�̒l
	mMoveSpeed = 20.0f;
	mGravity   = 2.0f;
	mLife	   = 3;

	//��������Player�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponent = new MeshComponent(this);

	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	//�G�t�F�N�g
	mSandEffectManager = new SandEffectManager(this, _ObjectTag, _SceneTag);
	mCheckpointEffectManager = new CheckpointEffectManager(_ObjectTag, _SceneTag, this);
	mClearEffectManager = new ClearEffectManager(_ObjectTag, _SceneTag, this);
	mDeathEffectManager = new DeathEffectManager(_ObjectTag, _SceneTag , this);

	//�v���C���[���g�̓����蔻��
	mSelfSphereCollider = new SphereCollider(this, GetOnCollisionFunc());
	Sphere sphere = {Vector3::sZERO, 30.0f};
	mSelfSphereCollider->SetObjectSphere(sphere);

	mLateralMoveVelocity = Vector3::sZERO;
	mButtonFlag = false;

	mMainCamera->SetPlayerPtr(this);
}

/*
@fn		�v���C���[�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void Player::UpdateGameObject(float _deltaTime)
{
	//�J�����̍��W
	const Vector3 CameraPos = Vector3(0, 500, -550);
	//�_���[�W���󂯂�y���W
	const float DamageYPos = -700.0f;
	//�S�[��z���W
	float goalZPos = 0.0f;

	//�v���C���[�̎΂ߌ��ɃJ�������Z�b�g
	mMainCamera->SetViewMatrixLerpObject(CameraPos, mPosition);

	//�X�e�[�W�N���A������v���C���[�̍X�V���~�߂�
	if (mClearFlag)
	{
		SetState(State::eDead);
	}

	//�v���C���[��������̍��W�܂ŗ�������_���[�W���󂯂�
	if (mPosition.y <= DamageYPos)
	{
		mPosition.y = DamageYPos + 1.0f;
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
		mLateralMoveVelocity = Vector3::sZERO;
		mCollisionFlag = true;

		if (mLife >= 1)
		{
			mPosition = mRespawnPos;
			mStopFlag = true;
		}
	}

	//�`���[�g���A��
	if (mScene == SceneBase::Scene::eTutorial)
	{
		//�`���[�g���A�����̑O���ړ����x
		mMoveSpeed = 13.0f;
		//�`���[�g���A�����̃W�����v��
		if (mJumpFlag)
		{
			mLateralMoveVelocity = Vector3::sZERO;
			mVelocity.y = 48.0f;
			mScaleFlag = true;
			mJumpFlag = false;
		}

		goalZPos = -75700.0f;

		//�`���[�g���A�����̃S�[���̍��W
		if (mPosition.z >= goalZPos)
		{
			mClearFlag = true;
		}
	}

	//�X�e�[�W01
	if (mScene == SceneBase::Scene::eStage01)
	{
		//�X�e�[�W01�̃W�����v��
		if (mJumpFlag)
		{
			mLateralMoveVelocity = Vector3::sZERO;
			mVelocity.y = 40.0f;
			mScaleFlag = true;
			mJumpFlag = false;
		}

		goalZPos = -8900.0f;

		//�X�e�[�W01�̃S�[�����W
		if (mPosition.z >= goalZPos)
		{
			mClearFlag = true;
		}
	}

	//�X�e�[�W02
	if (mScene == SceneBase::Scene::eStage02)
	{
		//�X�e�[�W02�̃W�����v��
		if (mJumpFlag)
		{
			mLateralMoveVelocity = Vector3::sZERO;
			mVelocity.y = 40.0f;
			mScaleFlag = true;
			mJumpFlag = false;
		}

		goalZPos = -2100.0f;

		//�X�e�[�W02�̃S�[���̍��W
		if (mPosition.z >= goalZPos)
		{
			mClearFlag = true;
		}
	}

	//���X�|�[����̑ҋ@���Ԓ�����
	if (mStopFlag)
	{
		//�\������^�C�~���O
		const int VisibleTiming = 10;

		mAngle = 0.0f;
		mVisibleFrameCount++;

		switch (mVisibleFrameCount % VisibleTiming)
		{
		case VisibleType::eInvisible:
			mMeshComponent->SetVisible(false);
			break;
		case VisibleType::eVisible:
			mMeshComponent->SetVisible(true);
			break;
		}

		//�\��������t���[��
		const int VisibleFlame = 40;

		mVelocity = Vector3::sZERO;
		if (mVisibleFrameCount >= VisibleFlame)
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
		SetState(State::eDead);
	}

	///////////////////////////////////////////////////////
	//�X�P�[���k������
	if (mScaleFlag)
	{

		mScale.y = 1.2f + (mPosition.y - MGroundYPos) * 0.0015f;
		mScale.z = 1.2f + (mPosition.y - MGroundYPos) * 0.0015f;
	}

	if (mPosition.y <= MGroundYPos && mVelocity.y <= 0.0f)
	{
		mScaleFlag = false;
		mScale.x = 1.2f;
		mScale.y = 1.2f;
		mScale.z = 1.2f;
	}
	///////////////////////////////////////////////////////

	//��]����y���W
	const float RotateYPos = 200.0f;

	//�W�����v�����Ƃ��ɉ�]��x�����鏈��
	if (mPosition.y >= RotateYPos)
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
	Quaternion inc(Vector3::sUNIT_X, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
	
	//�ő呬�x
	const float PlayerMaxSpeed = 25.0f;

	//�E�ړ��̍ő呬�x
	if (mVelocity.x >= PlayerMaxSpeed)
	{
		mVelocity.x = PlayerMaxSpeed;
	}
	//���ړ��̍ő呬�x
	if (mVelocity.x <= -PlayerMaxSpeed)
	{
		mVelocity.x = -PlayerMaxSpeed;
	}

	//// ��ɑO�ɐi��
	//if (!mStopFlag)
	//{
	//	mVelocity.z = mMoveSpeed;
	//}

	//�{�^���������Ă��Ȃ��Ƃ��̌�������
	if (!mButtonFlag)
	{
		//�����x
		const float PlayerSpeedDown = 4.0f;

		//���x��0���傫�������ꍇ�ɉE�Ɍ���
		if (mVelocity.x > 0.0f)
		{
			mVelocity.x += -PlayerSpeedDown;
		}
		//���x��0��菬���������ꍇ�ɍ��Ɍ���
		else if (mVelocity.x < 0.0f)
		{
			mVelocity.x += PlayerSpeedDown;
		}
		
		//���x�������x�̒l�ƈꏏ�ɂȂ����瑬�x��0�ɌŒ肷��
		if (mVelocity.x <= PlayerSpeedDown && mVelocity.x > 0.0f ||
			mVelocity.x >= -PlayerSpeedDown && mVelocity.x < 0.0f)
		{
			mVelocity.x = 0.0f;
		}

	}

	////�ڒn���Ă��Ȃ������X�|�[�����̑ҋ@���Ԃ���Ȃ����ɏd�͏������s��
	//if (!mGroundFlag && !mStopFlag)
	//{
	//	mVelocity.y -= mGravity;
	//}

	//�����蔻��𖳌��ɂ���y���W
	const float OffCollisionYPos = 50.0f;

	//�v���C���[��������̍��W�܂ŗ������瓖���蔻��𖳌��ɂ���
	if (mPosition.y < OffCollisionYPos)
	{
		mCollisionFlag = false;
	}

	//�`�F�b�N�|�C���g�G�t�F�N�g�𐧌�
	CheckpointEffectControl();

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
@fn	�`�F�b�N�|�C���g�G�t�F�N�g�𐧌�
*/
void Player::CheckpointEffectControl()
{
	//�`�F�b�N�|�C���g�{�[�h�ɓ���������G�t�F�N�g�𔭐����邽�߂̃J�E���g���n�߂�
	if (mHitCheckpointFlag)
	{
		//���Z�b�g����^�C�~���O
		const int ResetNum = 60;

		mCheckpointEffectCount++;

		//�G�t�F�N�g�̃t���O��J�E���g�𐔃t���[����Ƀ��Z�b�g����
		if (mCheckpointEffectCount >= ResetNum)
		{
			mHitCheckpointFlag = false;
			mCheckpointEffectCount = 0;
		}

		//�J�E���g���n�߂čŏ���1�t���[������1�񂾂��G�t�F�N�g�𔭐�������
		if (mCheckpointEffectCount == 1)
		{
			mEnableCheckpointFlag = true;
		}
		else
		{
			mEnableCheckpointFlag = false;
		}
	}
}

/*
@fn		���͂������Ŏ󂯎��X�V�֐�
@brief	��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
@param	_KeyState �e���͋@��̓��͏��
@brief	�L�[�{�[�h�A�}�E�X�A�R���g���[���[
*/
void Player::GameObjectInput(const InputState& _KeyState)
{
	//�R���g���[���[���͏���
	InputController(_KeyState);
	//�A�i���O�X�e�B�b�N���͏���
	InputStick(_KeyState);
}

/*
@fn �R���g���[���[���͏���
@param	_KeyState �e���͋@��̓��͏��
*/
void Player::InputController(const InputState& _KeyState)
{
	// �R���g���[���[�̏\����������̓L�[�{�[�h�AW�����͂��ꂽ��z�𑫂�
	if (_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 1 ||
		_KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
	{
		mVelocity.z = mMoveSpeed;
	}
	// �R���g���[���[�̏\�����������́A�L�[�{�[�hS�����͂��ꂽ��-z�𑫂�
	else if (_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1 ||
			 _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
	{
		mVelocity.z = -mMoveSpeed;
	}
	// �R���g���[���[�̏\���ォ�R���g���[���[�̏\�������L�[�{�[�hW���L�[�{�[�hS�����͂���Ȃ������瑬�x��0�ɂ���
	else if (_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 0  ||
			 _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 0||
			 _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) == 0 ||
			 _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) == 0)
	{
		mVelocity.z *= 0;
	}

	//�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ��-x�𑫂�
	if (_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 ||
		_KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
	{
		mVelocity.x += -MPlayerSpeedUp;
	}
	// �R���g���[���[�̏\���E�������́A�L�[�{�[�hD�����͂��ꂽ��x�𑫂�
	else if (_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 ||
		     _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
	{
		mVelocity.x += MPlayerSpeedUp;
	}

	// �R���g���[���[�̏\�������R���g���[���[�̏\���E���L�[�{�[�hA���L�[�{�[�hD�����͂���Ȃ�������mButtonFlag��false�ɂ���
	else if (_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 0 ||
		     _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 0 ||
		     _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) == 0 ||
		     _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) == 0)
	{
		mButtonFlag = false;
	}

}

/*
@fn �A�i���O�X�e�B�b�N���͏���
@param	_KeyState �e���͋@��̓��͏��
*/
void Player::InputStick(const InputState& _KeyState)
{
	//���X�e�B�b�N�̓��͒l�̒l(-1~1)
	Vector2 leftAxis = _KeyState.m_controller.GetLAxisVec();
	//�ړ����邽�߂̍��X�e�B�b�N�̂������l
	const float LeftAxisThreshold = 0.3f;

	//���X�e�B�b�N���͎��̍��ړ�
	if (leftAxis.x <= -LeftAxisThreshold)
	{
		mVelocity.x += -MPlayerSpeedUp;
	}
	//���X�e�B�b�N���͎��̉E�ړ�
	if (leftAxis.x >= LeftAxisThreshold)
	{
		mVelocity.x += MPlayerSpeedUp;
	}
}

/*
@fn		�v���C���[���q�b�g�������̏���
@param	_HitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
*/
void Player::OnCollision(const GameObject& _HitObject)
{
	if (mCollisionFlag)
	{
		//�q�b�g�����I�u�W�F�N�g�̃^�O���擾
		mTag = _HitObject.GetTag();

		//�_���[�W����
		if (mTag == Tag::eBlockTag ||
			mTag == Tag::eVerticalBlockTag ||
			mTag == Tag::eRightBlockTag ||
			mTag == Tag::eLeftBlockTag ||
			mTag == Tag::eRightOneMoveBlockTag ||
			mTag == Tag::eLeftOneMoveBlockTag ||
			mTag == Tag::eAerialBlockTag ||
			mTag == Tag::eLowUpBlockTag)
		{
			mDamageFlag = true;
		}

		//�ڒn����
		if (mTag == Tag::eGroundTag ||
			mTag == Tag::eGlassTag ||
			mTag == Tag::eVerticalMoveGroundTag ||
			mTag == Tag::eRightGroundTag ||
			mTag == Tag::eLeftGroundTag ||
			mTag == Tag::eLateralMoveGroundTag ||
			mTag == Tag::eJumpTag ||
			mTag == Tag::eDownBlockTag)
		{
			//�d�͂�����
			mVelocity.y = 0;
			mGroundFlag = true;
		}

		//�W�����v����
		if (mTag == Tag::eJumpTag)
		{
			mJumpFlag = true;
		}

		//���ړ����̔���
		if (mTag == Tag::eLateralMoveGroundTag)
		{
			//�d�͂�����
			mVelocity.y = 0;
			//���ړ����̑��x���擾
			mLateralMoveVelocity = mLateral->GetVelocity();
		}
		else
		{
			mLateralMoveVelocity = Vector3::sZERO;
		}

		//�`�F�b�N�|�C���g�ɓ����������̏���
		HitCheckPoint(_HitObject);
	}
}

/*
@fn	    �`�F�b�N�|�C���g�ɓ����������̏���
@param	_HitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
*/
void Player::HitCheckPoint(const GameObject& _HitObject)
{
	//�`�F�b�N�|�C���g�ʉߔ���
	if (mTag == Tag::eCheckpointTag)
	{
		//���X�|�[���n�_�������O�ɂ��炷���߂̒萔
		const Vector3 ShiftZPos = Vector3(0.0f, 0.0f, 100.0f);
		mGroundFlag = false;
		mHitCheckpointFlag = true;
		mRespawnPos = _HitObject.GetPosition() + ShiftZPos;

		if (mPosition.y <= MGroundYPos)
		{
			mGroundFlag = true;
		}
	}
}