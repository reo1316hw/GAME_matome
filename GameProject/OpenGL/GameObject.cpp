/*
@brief �C���N���[�h
*/
#include "pch.h"

//�Q�[���I�u�W�F�N�g��ID�A�J�E���g�p�̏�����
int GameObject::mGameObjectId = 0;
//���C���J�����̏������@������GameObjectManager�������ɍs����
MainCameraObject* GameObject::mMainCamera = nullptr;
//�Q�[���I�u�W�F�N�g�̍X�V���~�߂�C�x���g��Ԃ̏�����
PauzingEvent GameObject::mPauzingEvent = PauzingEvent::NoneEvent;

/*
@fn		�R���X�g���N�^
@param	_SceneTag �V�[���̃^�O
@param	_ObjectTag �Q�[���I�u�W�F�N�g�̃^�O
@param	_reUseGameObject
*/
GameObject::GameObject(SceneBase::Scene _SceneTag,const Tag& _ObjectTag, bool _reUseGameObject)
	: mState(Active)
	, mWorldTransform()
	, mPosition(Vector3::sZERO)
	, mVelocity(Vector3::sZERO)
	, mAabb(Vector3::sZERO, Vector3::sZERO)
	, mScale(Vector3(1.0f, 1.0f, 1.0f))
	, mRotation(Quaternion::sIDENTITY)
	, mMyObjectId(mGameObjectId)
	, mTag(_ObjectTag)
	, mSceneTag(_SceneTag)
	, mMoveSpeed(0.0f)
	, mGravity(0.0f)
	, mReUseObject(_reUseGameObject)
	, mRecomputeWorldTransform(true)
	, mHitFlag(false)
{
	mGameObjectId++;
	//GameObjectManager�Ƀ|�C���^��n��
	GAME_OBJECT_MANAGER->AddGameObject(this);
}

/*
@fn	�f�X�g���N�^
*/
GameObject::~GameObject()
{
	//GameObjectManager����|�C���^���폜����
	GAME_OBJECT_MANAGER->RemoveGameObject(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}

}

/*
@fn		�t���[�����̏���
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void GameObject::Update(float _deltaTime)
{
	//�X�V��~�̃C�x���g���łȂ���(�|�[�Y��ʂȂ�)
	if (mPauzingEvent == PauzingEvent::NoneEvent)
	{
		if (mState == Active)
		{
			//Transform�̃��[���h�ϊ�
			ComputeWorldTransform();
			//�Q�[���I�u�W�F�N�g�̍X�V
			UpdateGameObject(_deltaTime);
			//���̃Q�[���I�u�W�F�N�g�ɕt������R���|�[�l���g�̍X�V
			UpdateComponents(_deltaTime);
			//Transform�̃��[���h�ϊ�
			ComputeWorldTransform();
		}
	}
	//�|�[�Y��ʂ̂Ƃ��R���|�[�l���g���X�V�����Ȃ�(�A�j���[�V�����Ȃǂ��~�߂邽��)
	else if(mPauzingEvent == PauzingEvent::PausingEvent)
	{
		PausingUpdateGameObject();
	}
	else
	{
		PausingUpdateGameObject();
		UpdateComponents(_deltaTime);
	}
}

/*
@fn		�A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void GameObject::UpdateComponents(float _deltaTime)
{
	if (mState != Dead)
	{	
		for (auto itr : mComponents)
		{
			itr->Update(_deltaTime);
		}
	}
}

/*
@fn		�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void GameObject::UpdateGameObject(float _deltaTime)
{
}

/*
@fn		�Q�[���I�u�W�F�N�g���Î~���ɍX�V�����A�b�v�f�[�g�֐�
@brief	pauzingUpdate��true�̂Ƃ������Ă΂��X�V�֐�
*/
void GameObject::PausingUpdateGameObject()
{
}

/*
@fn		���͏�Ԃ��󂯎��GameObject��Component�̓��͍X�V�֐����Ăяo��
@param	_KeyState �e���͋@��̓��͏��
@brief	�L�[�{�[�h�A�}�E�X�A�R���g���[���[
*/
void GameObject::ProcessInput(const InputState& _KeyState)
{
	if (mState == Active)
	{
		//�R���|�[�l���g�̓��͊֐��ɃR���g���[���[�̓��͏�Ԃ�
		for (auto comp : mComponents)
		{
			comp->ProcessInput(_KeyState);
		}
		//�Q�[���I�u�W�F�N�g�̓��͊֐��ɃR���g���[���[�̓��͏�Ԃ�
		GameObjectInput(_KeyState);
	}
}

/*
@fn		���͂������Ŏ󂯎��X�V�֐�
@brief	��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
@param	_KeyState �e���͋@��̓��͏��
@brief	�L�[�{�[�h�A�}�E�X�A�R���g���[���[
*/
void GameObject::GameObjectInput(const InputState & _KeyState)
{
}

/*
@fn		�R���|�[�l���g��ǉ�����
@param	_component �ǉ�����R���|�[�l���g�̃|�C���^
*/
void GameObject::AddComponent(Component * _component)
{
	int order = _component->GetUpdateOder();
	auto itr = mComponents.begin();
	for (;
		itr != mComponents.end();
		++itr)
	{
		if (order < (*itr)->GetUpdateOder())
		{
			break;
		}
	}
	mComponents.insert(itr, _component);
}

/*
@fn		�R���|�[�l���g���폜����
@param	_component �폜����R���|�[�l���g�̃|�C���^
*/
void GameObject::RemoveComponent(Component * _component)
{
	auto itr = std::find(mComponents.begin(), mComponents.end(), _component);
	if (itr != mComponents.end())
	{
		mComponents.erase(itr);
	}
}

/*
@fn			���݂̎d�l��s�����Ƃ��ł��Ȃ��������O�����狭���ɍs�����߂̊֐�
@exsample	�Q�[���I�u�W�F�N�g�S�̂̍X�V����~���ɑΏۂ̃Q�[���I�u�W�F�N�g���X�V����
*/
void GameObject::ExceptionUpdate()
{
	ComputeWorldTransform();

	UpdateGameObject(0.016f);
	UpdateComponents(0.016f);

	ComputeWorldTransform();
}

/*
@fn	Transform�̃��[���h�ϊ�
*/
void GameObject::ComputeWorldTransform()
{
	//���[���h�ϊ����K�v���ǂ����H
	//�����K�v�������烏�[���h�ϊ����s��
	if (mRecomputeWorldTransform)
	{
		//object��
		//�ϊ����K�v�t���O���~�낷
		mRecomputeWorldTransform = false;
		//�X�P�[���̃��[���h�ϊ�
		mWorldTransform = Matrix4::CreateScale(mScale);
		//��]�̃��[���h�ϊ��i�N�E�H�[�^�j�I���j
		mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
		//���s�ړ��̍X�V
		mWorldTransform *= Matrix4::CreateTranslation(mPosition);

		//object�iowner�j�������Ă���component�ɂ����W�ϊ��n
		for (auto itr : mComponents)
		{
			itr->OnUpdateWorldTransform();
		}
	}
}

/*
@fn		��`�Ƌ�`�̉����߂�
@param	_MyAABB	��ɂ���I�u�W�F�N�g�̋�`�����蔻��
@param	_PairAABB �q�b�g����I�u�W�F�N�g�̋�`�����蔻��
@param	_PairTag �q�b�g����I�u�W�F�N�g�̃^�O
*/
void GameObject::FixCollision(const AABB & _MyAABB, const AABB & _PairAABB, const Tag& _PairTag)
{
	Vector3 ment = Vector3(0, 0, 0);
	CalcCollisionFixVec(_MyAABB, _PairAABB, ment);
	SetPosition(GetPosition() + (ment));
}

/*
@fn		�O���x�N�g���̌����ɉ�]����
@param	_forward �����������O�������x�N�g��
*/
void GameObject::RotateToNewForward(const Vector3& _Forward)
{
	// X���x�N�g��(1,0,0)��forward�̊Ԃ̊p�x�����߂�
	float dot = Vector3::Dot(Vector3::sUNIT_X, _Forward);
	float angle = Math::Acos(dot);
	//printf("%f\n", angle);
	// �������������ꍇ
	if (dot > 0.9999f)
	{
		SetRotation(Quaternion::sIDENTITY);
	}
	// ������������ꍇ
	else if (dot < -0.9999f)
	{
		SetRotation(Quaternion(Vector3::sUNIT_Z, Math::Pi));
	}
	else
	{
		// ���x�N�g����forward�Ƃ̊O�ς����]�������Ƃ߁A��]������
		Vector3 axis = Vector3::Cross(Vector3::sUNIT_X, _Forward);
		axis.Normalize();
		SetRotation(Quaternion(axis, angle));
	}
}

/*
@fn �ÓI��mainCamera�𐶐�����
*/
void GameObject::CreateMainCamera()
{
	mMainCamera = new MainCameraObject();
}