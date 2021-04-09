#pragma once
#include <vector>
#include <functional>
#include "Math.h"
#include "Collision.h"
#include "SceneBase.h"

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
	Active,
	//�X�V����~���Ă���
	Paused,
	//�I�u�W�F�N�g�̍X�V���I��(�O������̂�Active�ɕύX�\)
	Dead,
};

/*
@enum	GameObject�^�O
@brief	�Փˑ���𔻕ʂ��邽�߂Ɏg�p
*/
enum Tag
{
	Other = 0,
	Camera = 1,
	player = 2,
	ground = 3,
	glass = 4,
	block = 5,
	verticalMoveGround = 6,
	jump = 7,
	lateralMoveGround = 8,
	upBlock = 9,
	upBlock_02 = 10,
	verticalBlock = 11,
	aerialBlock = 12,
	rightBlock = 13,
	leftBlock = 14,
	rightOneBlock = 15,
	rightOneBlock_02 = 16,
	leftOneBlock = 17,
	leftOneBlock_02 = 18,
	downBlock = 19,
	goalBlock = 20,
	respawn01 = 21,
	respawn02 = 22,
	respawn03 = 23,
	Swith = 24
};

/*
@enum	�Q�[���I�u�W�F�N�g�̍X�V���~����C�x���g��
*/
enum PauzingEvent
{
	//�{�X�̓��ꉉ�o
	SummonMageEvent,
	//�|�[�Y��ʒ�
	PausingEvent,
	//�v���C���[�����j����Ă��܂����ۂ̉��o
	DeadPlayerEvent,
	//�Q�[���I�[�o�[���̉��o DeadPlayerEvent�Ɗ֘A
	GameOverEvent,
	//�Q�[���I�u�W�F�N�g�̍X�V���s���Ă���B
	NoneEvent
};

class GameObject
{
public:
	/*
	@fn		�R���X�g���N�^
	@param	_sceneTag �V�[���̃^�O
	@param	_objectTag �Q�[���I�u�W�F�N�g�̃^�O
	@param	_reUseGameObject
	*/
	GameObject(SceneBase::Scene _sceneTag, const Tag& _objectTag , bool _reUseGameObject = false);

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
	@fn �Q�[���I�u�W�F�N�g���Î~���ɍX�V�����A�b�v�f�[�g�֐�
	@brief pauzingUpdate��true�̂Ƃ������Ă΂��X�V�֐�
	*/
	virtual void PausingUpdateGameObject();

	/*
	@fn ���͏�Ԃ��󂯎��GameObject��Component�̓��͍X�V�֐����Ăяo��
	*/
	void ProcessInput(const InputState& _keyState);

	/*
	@fn ���͂������Ŏ󂯎��X�V�֐�
	@brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
	*/
	virtual void GameObjectInput(const InputState& _keyState);

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

	virtual void FixCollision(const AABB& _myAABB, const AABB& _pairAABB, const Tag& _pairTag);

	void RotateToNewForward(const Vector3& _forward);

	/*
	@fn �ÓI��mainCamera�𐶐�����
	*/
	static void CreateMainCamera();

protected:
	std::function<void(GameObject&)> GetOnCollisionFunc() { return std::bind(&GameObject::OnCollision, this, std::placeholders::_1); }
	virtual void OnCollision(const GameObject& _hitObject) {}

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
	//�Q�[���I�u�W�F�N�g�̓����蔻��
	BoxCollider* mBoxcollider;
	//�����蔻���mesh�ɂ��邽�߂̃C���X�^���X
	Mesh* mMesh;

	//Transform
	Vector3 mPosition;
	Vector3 mVelocity;
	Vector3 mScale;
	//�@�ړ���
	Vector3 mEndPos;
	//�@�������W
	Vector3		mInitPos;
	Quaternion  mRotation;
	Matrix4		mWorldTransform;
	// �ړ����x
	float mMoveSpeed;
	//�d��
	float mGravity;
	//���[���h�ϊ��̏������s���K�v�������邩
	bool mRecomputeWorldTransform;
	// �����������ǂ���
	bool mHitFlag;
	// ���X�|�[��������
	bool mRespawnFlag;
	// �����ʒu�ɖ߂���
	bool mOriginalPosFlag;
	
	//�V�[���̃^�O
	SceneBase::Scene mSceneTag;
	//�A�^�b�`����Ă���R���|�[�l���g
	std::vector<class Component*>mComponents;
private:

	//�V�[�����ׂ��ۂɉ�������I�u�W�F�N�g���ǂ����A�J�����Ȃǂ��ΏۂɂȂ�
	bool mReUseObject;

public://�Q�b�^�[�Z�b�^�[

	/*
	@return	�I�u�W�F�N�g�̃|�W�V����
	*/
	const Vector3& GetPosition() const { return mPosition; }

	bool GetRecomputeWorldTransform() { return mRecomputeWorldTransform; }

	/*
	@return	�I�u�W�F�N�g�̃X�P�[��
	*/
	Vector3 GetScaleFloat() const { return mScale; }

	float GetScale() { return mScale.x; }
	/*
	@brief�@�I�u�W�F�N�g�̃N�H�[�^�j�I�����擾����
	@return	rotation�iQuaternion�^�j
	*/
	const Quaternion& GetRotation() const { return mRotation; }

	/*
	@brief�@�I�u�W�F�N�g�̏�Ԃ��擾����
	@return	state
	*/
	State GetState() const { return mState; }

	/*
	@brief�@�I�u�W�F�N�g�̃��[���h�s����擾����
	@return	worldTransform
	*/
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	/*
	@brief�@�I�u�W�F�N�g�̑O����\���x�N�g�����擾����
	@param	forward(Vector3�^)
	*/
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitZ, mRotation); }

	/*
	@brief�@�I�u�W�F�N�g�̉E��\���x�N�g�����擾����
	@param	right(Vector3�^)
	*/
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitX, mRotation); }

	/*
	@brief�@�I�u�W�F�N�g�̏��\���x�N�g�����擾����
	@param	up(Vector3�^)
	*/
	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitY, mRotation); };

	/*
	@brief�@�I�u�W�F�N�g�̃^�O���擾����
	@return	tag
	*/
	Tag GetTag() const { return mTag; };

	/*
	@brief�@�I�u�W�F�N�g��id���擾����
	@return	myObjectId(int�^)
	*/
	int GetObjectId() { return mMyObjectId; };

	/*
	@brief�@��������I�u�W�F�N�g���擾����
	@return	reUseObject(bool�^)
	*/
	bool GetReUseGameObject() { return mReUseObject; };

	/*
	@brief�@�V�[���̃^�O���擾����
	@return	sceneTag
	*/
	SceneBase::Scene GetScene() { return mSceneTag; };

	/*
	@brief�@�I�u�W�F�N�g��AABB���擾����
	@return	aabb
	*/
	AABB GetObjectAABB() { return mAabb; };

	/*
	@param	_scale �I�u�W�F�N�g�̃X�P�[��
*/
	void SetScale(Vector3 _scale) { mScale.x = _scale.x; mScale.y = _scale.y; mScale.z = _scale.z; mRecomputeWorldTransform = true; }

	/*
	@brief�@�I�u�W�F�N�g�̃N�H�[�^�j�I����ݒ肷��
	@param	rotation�iQuaternion�^�j
	*/
	virtual void SetRotation(const Quaternion& _qotation) { mRotation = _qotation;  mRecomputeWorldTransform = true; }


	/*
	@param	_state �I�u�W�F�N�g�̏��
	*/
	virtual void SetState(State _state) { mState = _state; }

	/*
	@param	_pos �I�u�W�F�N�g�̃|�W�V����
	*/
	virtual void SetPosition(const Vector3& _pos) { mPosition = _pos; mRecomputeWorldTransform = true; }

};

