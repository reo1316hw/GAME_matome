/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class Game;
class Vector3;
class Matrix4;
class Component;
class ColliderComponent;
class InvisibleMeshComponent;
class MeshComponent;
class Mesh;
class BoxCollider;
struct InputState;

/*
@enum	GameObject�X�e�[�g
@brief	�Q�[���I�u�W�F�N�g�̏��
*/
enum State
{
	//�A�N�e�B�u
	eActive,
	//�X�V����~���Ă���
	ePaused,
	//�I�u�W�F�N�g�̍X�V���I��(�O������̂�Active�ɕύX�\)
	eDead,
};

/*
@enum	GameObject�^�O
@brief	�Փˑ���𔻕ʂ��邽�߂Ɏg�p
*/
enum Tag
{
	eOtherTag = 0,
	eCameraTag = 1,
	ePlayerTag = 2,
	eGroundTag = 3,
	eGlassTag = 4,
	eBlockTag = 5,
	eVerticalMoveGroundTag = 6,
	eJumpTag = 7,
	eLateralMoveGroundTag = 8,
	eLowUpBlockTag = 9,
	eHighUpBlockTag = 10,
	eVerticalBlockTag = 11,
	eAerialBlockTag = 12,
	eRightBlockTag = 13,
	eLeftBlockTag = 14,
	eRightGroundTag = 15,
	eRightOneMoveBlockTag = 16,
	eLeftGroundTag = 17,
	eLeftOneMoveBlockTag = 18,
	eDownBlockTag = 19,
	eGoalBlockTag = 20,
	eGoalWarpHoleTag = 21,
	eGoalCircleFrameTag = 22,
	eCheckpointTag = 23,
};

/*
@enum	�Q�[���I�u�W�F�N�g�̍X�V���~����C�x���g��
*/
enum PauzingEvent
{
	//�{�X�̓��ꉉ�o
	eSummonMageEvent,
	//�|�[�Y��ʒ�
	ePausingEvent,
	//�v���C���[�����j����Ă��܂����ۂ̉��o
	eDeadPlayerEvent,
	//�Q�[���I�[�o�[���̉��o DeadPlayerEvent�Ɗ֘A
	eGameOverEvent,
	//�Q�[���I�u�W�F�N�g�̍X�V���s���Ă���B
	eNoneEvent
};

class GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_SceneTag �V�[���̃^�O
	@param	_ObjectTag �Q�[���I�u�W�F�N�g�̃^�O
	@param	_reUseGameObject
	*/
	GameObject(SceneBase::Scene _SceneTag, const Tag& _ObjectTag , bool _reUseGameObject = false);

	/*
	@fn	�f�X�g���N�^
	*/
	virtual ~GameObject();

	/*
	@fn		�t���[�����̏���
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Update(float _deltaTime);

	/*
	@fn		�A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateComponents(float _deltaTime);

	/*
	@fn		�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	virtual void UpdateGameObject(float _deltaTime);

	/*
	@fn		�Q�[���I�u�W�F�N�g���Î~���ɍX�V�����A�b�v�f�[�g�֐�
	@brief	pauzingUpdate��true�̂Ƃ������Ă΂��X�V�֐�
	*/
	virtual void PausingUpdateGameObject();

	/*
	@fn		���͏�Ԃ��󂯎��GameObject��Component�̓��͍X�V�֐����Ăяo��
	@param	_KeyState �e���͋@��̓��͏��
	@brief	�L�[�{�[�h�A�}�E�X�A�R���g���[���[
	*/
	void ProcessInput(const InputState& _KeyState);

	/*
	@fn		���͂������Ŏ󂯎��X�V�֐�
	@brief	��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
	@param	_KeyState �e���͋@��̓��͏��
	@brief	�L�[�{�[�h�A�}�E�X�A�R���g���[���[
	*/
	virtual void GameObjectInput(const InputState& _KeyState);

	/*
	@fn		�R���|�[�l���g��ǉ�����
	@param	_component �ǉ�����R���|�[�l���g�̃|�C���^
	*/
	void AddComponent(Component* _component);

	/*
	@fn		�R���|�[�l���g���폜����
	@param	_component �폜����R���|�[�l���g�̃|�C���^
	*/
	void RemoveComponent(Component* _component);

	/*
	@fn			���݂̎d�l��s�����Ƃ��ł��Ȃ��������O�����狭���ɍs�����߂̊֐�
	@exsample	�Q�[���I�u�W�F�N�g�S�̂̍X�V����~���ɑΏۂ̃Q�[���I�u�W�F�N�g���X�V����
	*/
	void ExceptionUpdate();

	/*
	@fn	Transform�̃��[���h�ϊ�
	*/
	void ComputeWorldTransform();

	/*
	@fn		��`�Ƌ�`�̉����߂�
	@param	_MyAABB	��ɂ���I�u�W�F�N�g�̋�`�����蔻��
	@param	_PairAABB �q�b�g����I�u�W�F�N�g�̋�`�����蔻��
	@param	_PairTag �q�b�g����I�u�W�F�N�g�̃^�O
	*/
	virtual void FixCollision(const AABB& _MyAABB, const AABB& _PairAABB, const Tag& _PairTag);

	/*
	@fn		�O���x�N�g���̌����ɉ�]����
	@param	_forward �����������O�������x�N�g��
	*/
	void RotateToNewForward(const Vector3& _Forward);

	/*
	@fn �ÓI��mainCamera�𐶐�����
	*/
	static void CreateMainCamera();

protected:

	std::function<void(GameObject&)> GetOnCollisionFunc() { return std::bind(&GameObject::OnCollision, this, std::placeholders::_1); }

	/*
	@fn		�Q�[���I�u�W�F�N�g���q�b�g�������̏���
	@param	_hitObject �q�b�g�����Ώۂ̃Q�[���I�u�W�F�N�g�̃A�h���X
	*/
	virtual void OnCollision(const GameObject& _HitObject) {}

	//���C���J�����@������GameObjectManager�������ɍs����
	static class MainCameraObject* mMainCamera;
	//�Q�[���I�u�W�F�N�g�̍X�V���~�߂�C�x���g���
	static PauzingEvent mPauzingEvent;
	//�Փˎ��̃��A�N�V�����֐�(ColliderComponent�ɂ��̊֐��̃A�h���X��n��) Enter...�Փ˂��� Stay...�Փ˂��Ă���
	virtual void OnTriggerEnter(ColliderComponent* _colliderPair) {};
	//�Փˎ��̃��A�N�V�����֐�(ColliderComponent�ɂ��̊֐��̃A�h���X��n��) Enter...�Փ˂��� Stay...�Փ˂��Ă���
	virtual void OnTriggerStay(ColliderComponent* _colliderPair) {};

	//�I�u�W�F�N�g��AABB
	AABB mAabb;
	//�Q�[���I�u�W�F�N�g�̏��
	State mState;
	//�Q�[���I�u�W�F�N�g�̃^�O
	Tag mTag;
	//�Q�[���I�u�W�F�N�g��ID�A�J�E���g�p
	static int mGameObjectId;
	//���̃Q�[���I�u�W�F�N�g��ID
	int mMyObjectId;

	//�Q�[���I�u�W�F�N�g�̃��b�V��
	MeshComponent* mMeshComponent;
	//�Q�[���I�u�W�F�N�g�̋�`�����蔻��
	BoxCollider* mBoxcollider;
	//�����蔻���mesh�ɂ��邽�߂̃C���X�^���X
	Mesh* mMesh;

	//Transform
	Vector3 mPosition;
	Vector3 mVelocity;
	Vector3 mScale;
	//�ړ���
	Vector3 mEndPos;
	//�������W
	Vector3	mInitPos;
	//���X�|�[������n�_
	Vector3 mRespawnPos;
	//�I�u�W�F�N�g�̃N�H�[�^�j�I��
	Quaternion  mRotation;
	//�I�u�W�F�N�g�̃��[���h�s��
	Matrix4	mWorldTransform;
	//�ړ����x
	float mMoveSpeed;
	//�d��
	float mGravity;
	//���[���h�ϊ��̏������s���K�v�������邩
	bool mRecomputeWorldTransform;
	// �����������ǂ���
	bool mHitFlag;
	// �����ʒu�ɖ߂���
	bool mOriginalPosFlag;
	// ���X�|�[���t���O��ۑ����Ă����ϐ�
	bool mSaveRespawnFlag;
	
	//�V�[���̃^�O
	SceneBase::Scene mSceneTag;
	//�A�^�b�`����Ă���R���|�[�l���g
	std::vector<class Component*>mComponents;

private:

	//�V�[�����ׂ��ۂɉ�������I�u�W�F�N�g���ǂ����A�J�����Ȃǂ��ΏۂɂȂ�
	bool mReUseObject;

public://�Q�b�^�[�Z�b�^�[

	/*
	@return	�I�u�W�F�N�g�̃|�W�V����(Vector3�^)
	*/
	const Vector3& GetPosition() const { return mPosition; }

	/*
	@return	�I�u�W�F�N�g�̏������W(Vector3�^)
	*/
	const Vector3& GetInitPosition() const { return mInitPos; }

	/*
	@return	�I�u�W�F�N�g�̑��x(Vector3�^)
	*/
	const Vector3& GetVelocity() const { return mVelocity; }

	/*
    @return	���X�|�[������n�_(Vector3�^)
    */
	const Vector3 GetRespawnPos() const { return mRespawnPos; };

	/*
	@return	�I�u�W�F�N�g�̃X�P�[��(float�^)
	*/
	const float GetScale() const { return mScale.z; }

	/*
	@return	���[���h�ϊ��̏������s���K�v�������邩�̃t���O(bool�^)
	*/
	bool GetRecomputeWorldTransform() { return mRecomputeWorldTransform; }

	/*
    @return	���X�|�[���������̃t���O(bool�^)
    */
	bool GetRespawnFlag() { return mSaveRespawnFlag; };

	/*
	@return	�I�u�W�F�N�g�̃N�H�[�^�j�I��(Quaternion�^)
	*/
	const Quaternion& GetRotation() const { return mRotation; }

	/*
	@return	�I�u�W�F�N�g�̏��(enum�^ State)
	*/
	State GetState() const { return mState; }

	/*
	@return	�I�u�W�F�N�g�̃��[���h�s��(Matrix4�^)
	*/
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	/*
	@return	�I�u�W�F�N�g�̑O����\���x�N�g��(Vector3�^)
	*/
	Vector3 GetForward() const { return Vector3::Transform(Vector3::sUNIT_Z, mRotation); }

	/*
	@return	�I�u�W�F�N�g�̉E��\���x�N�g��(Vector3�^)
	*/
	Vector3 GetRight() const { return Vector3::Transform(Vector3::sUNIT_X, mRotation); }

	/*
	@return	�I�u�W�F�N�g�̏��\���x�N�g��(Vector3�^)
	*/
	Vector3 GetUp() const { return Vector3::Transform(Vector3::sUNIT_Y, mRotation); };

	/*
	@return	�I�u�W�F�N�g�̃^�O(enum�^ Tag)
	*/
	Tag GetTag() const { return mTag; };

	/*
	@return	�I�u�W�F�N�g��id(int�^)
	*/
	int GetObjectId() { return mMyObjectId; };

	/*
	@return	��������I�u�W�F�N�g(bool�^)
	*/
	bool GetReUseGameObject() { return mReUseObject; };

	/*
	@return	�V�[���̃^�O
	*/
	SceneBase::Scene GetScene() { return mSceneTag; };

	/*
	@return	�I�u�W�F�N�g��AABB
	*/
	AABB GetObjectAABB() { return mAabb; };

	/*
	@param	_scale �I�u�W�F�N�g�̃X�P�[��
	*/
	void SetScale(Vector3 _scale) { mScale.x = _scale.x; mScale.y = _scale.y; mScale.z = _scale.z; mRecomputeWorldTransform = true; }

	/*
	@param	_Qotation �I�u�W�F�N�g�̃N�H�[�^�j�I��
	*/
	virtual void SetRotation(const Quaternion& _Qotation) { mRotation = _Qotation;  mRecomputeWorldTransform = true; }

	/*
	@param	_state �I�u�W�F�N�g�̏��
	*/
	virtual void SetState(State _state) { mState = _state; }

	/*
	@param	_Pos �I�u�W�F�N�g�̃|�W�V����
	*/
	virtual void SetPosition(const Vector3& _Pos) { mPosition = _Pos; mRecomputeWorldTransform = true; }

};

