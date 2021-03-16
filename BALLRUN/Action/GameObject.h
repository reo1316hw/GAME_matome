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
class MeshComponent;
class Mesh;
class BoxCollider;
struct InputState;

/*
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
	@enum�@GameObject�^�O
	�Փˑ���𔻕ʂ��邽�߂Ɏg�p
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
@enum �Q�[���I�u�W�F�N�g�̍X�V���~����C�x���g��
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
	@param	�Q�[���N���X�̃|�C���^
	*/
	GameObject(SceneBase::Scene _sceneTag, const Tag& _objectTag , bool _reUseGameObject = false);
	virtual ~GameObject();

	/*
	@brief	�t���[�����̏���
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void Update(float _deltaTime);

	/*
	@brief	�A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateComponents(float _deltaTime);

	/*
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
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
	@brief	�R���|�[�l���g��ǉ�����
	@param	�ǉ�����R���|�[�l���g�̃|�C���^
	*/
	void AddComponent(Component* _component);

	/*
	@brief	�R���|�[�l���g���폜����
	@param	�폜����R���|�[�l���g�̃|�C���^
	*/
	void RemoveComponent(Component* _component);

	/*
	@fn ���݂̎d�l��s�����Ƃ��ł��Ȃ��������O�����狭���ɍs�����߂̊֐�
	@exsample �Q�[���I�u�W�F�N�g�S�̂̍X�V����~���ɑΏۂ̃Q�[���I�u�W�F�N�g���X�V����
	*/
	void ExceptionUpdate();
	/*
	@brief	Transform�̃��[���h�ϊ�
	*/
	void ComputeWorldTransform();

	/*
	@brief�@�I�u�W�F�N�g�̃|�W�V�������擾����
	@return	position
	*/
	const Vector3& GetPosition() const { return position; }

	/*
	@brief�@�I�u�W�F�N�g�̃|�W�V������ݒ肷��
	@param	position
	*/
	virtual void SetPosition(const Vector3& _pos) { position = _pos; recomputeWorldTransform = true; }
	bool GetRecomputeWorldTransform() { return recomputeWorldTransform; }

	/*
	@brief�@�I�u�W�F�N�g�̃X�P�[�����擾����
	@return	scale
	*/
	Vector3 GetScaleFloat() const { return scale; }

	/*
	@brief�@�I�u�W�F�N�g�̃X�P�[����ݒ肷��
	@param	scale
	*/
	void SetScale(float _scale) { scale.x = _scale; scale.y = _scale; scale.z = _scale; recomputeWorldTransform = true; }
	void SetScale(Vector3 _scale) { scale.x = _scale.x; scale.y = _scale.y; scale.z = _scale.z; recomputeWorldTransform = true; }

	float GetScale() { return scale.x; }
	/*
	@brief�@�I�u�W�F�N�g�̃N�H�[�^�j�I�����擾����
	@return	rotation�iQuaternion�^�j
	*/
	const Quaternion& GetRotation() const { return rotation; }

	/*
	@brief�@�I�u�W�F�N�g�̃N�H�[�^�j�I����ݒ肷��
	@param	rotation�iQuaternion�^�j
	*/
	virtual void SetRotation(const Quaternion& _qotation) { rotation = _qotation;  recomputeWorldTransform = true; }

	/*
	@brief�@�I�u�W�F�N�g�̏�Ԃ��擾����
	@return	state
	*/
	State GetState() const { return state; }

	/*
	@brief�@�I�u�W�F�N�g�̏�Ԃ�ݒ肷��
	@param	state
	*/
	virtual void SetState(State _state) { state = _state; }

	/*
	@brief�@�I�u�W�F�N�g�̃��[���h�s����擾����
	@return	worldTransform
	*/
	const Matrix4& GetWorldTransform() const { return worldTransform; }

	/*
	@brief�@�I�u�W�F�N�g�̑O����\���x�N�g�����擾����
	@param	forward(Vector3�^)
	*/
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitZ, rotation); }

	/*
	@brief�@�I�u�W�F�N�g�̉E��\���x�N�g�����擾����
	@param	right(Vector3�^)
	*/
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitX, rotation); }

	/*
	@brief�@�I�u�W�F�N�g�̏��\���x�N�g�����擾����
	@param	up(Vector3�^)
	*/
	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitY, rotation); };
	
	/*
	@brief�@�I�u�W�F�N�g�̃^�O���擾����
	@return	tag
	*/
	Tag GetTag() const { return tag; };

	/*
	@brief�@�I�u�W�F�N�g��id���擾����
	@return	myObjectId(int�^)
	*/
	int GetObjectId() { return myObjectId; };

	/*
	@brief�@��������I�u�W�F�N�g���擾����
	@return	reUseObject(bool�^)
	*/
	bool GetReUseGameObject() { return reUseObject; };

	virtual void FixCollision(const AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag);

	void RotateToNewForward(const Vector3& forward);

	/*
	@fn �ÓI��mainCamera�𐶐�����
	*/
	static void CreateMainCamera();

	/*
	@brief�@�V�[���̃^�O���擾����
	@return	sceneTag
	*/
	SceneBase::Scene GetScene() { return sceneTag; };

	/*
	@brief�@�I�u�W�F�N�g��AABB���擾����
	@return	aabb
	*/
	AABB GetObjectAABB() { return aabb; };

protected:
	std::function<void(GameObject&)> GetOnCollisionFunc() { return std::bind(&GameObject::OnCollision, this, std::placeholders::_1); }
	virtual void OnCollision(const GameObject& _hitObject) {}

	//���C���J�����@������GameObjectManager�������ɍs����
	static class MainCameraObject* mainCamera;
	//�Q�[���I�u�W�F�N�g�̍X�V���~�߂�C�x���g���
	static PauzingEvent pauzingEvent;
	//�Փˎ��̃��A�N�V�����֐�(ColliderComponent�ɂ��̊֐��̃A�h���X��n��) Enter...�Փ˂��� Stay...�Փ˂��Ă���
	virtual void OnTriggerEnter(ColliderComponent* colliderPair) {};
	//�Փˎ��̃��A�N�V�����֐�(ColliderComponent�ɂ��̊֐��̃A�h���X��n��) Enter...�Փ˂��� Stay...�Փ˂��Ă���
	virtual void OnTriggerStay(ColliderComponent* colliderPair) {};

	//�I�u�W�F�N�g��AABB
	AABB aabb;
	//�Q�[���I�u�W�F�N�g�̏��
	State state;
	//�Q�[���I�u�W�F�N�g�̃^�O
	Tag tag;
	//�Q�[���I�u�W�F�N�g��ID�A�J�E���g�p
	static int gameObjectId;
	//���̃Q�[���I�u�W�F�N�g��ID
	int myObjectId;

	//�Q�[���I�u�W�F�N�g�̃��b�V��
	MeshComponent* meshComponent;
	//�Q�[���I�u�W�F�N�g�̓����蔻��
	BoxCollider* boxcollider;
	//�����蔻���mesh�ɂ��邽�߂̃C���X�^���X
	Mesh* mesh;

	//Transform
	Vector3 position;
	Vector3 velocity;
	Vector3 scale;
	//�@�ړ���
	Vector3 endPos;
	//�@�������W
	Vector3 initPos;
	Quaternion rotation;
	Matrix4 worldTransform;
	// �ړ����x
	float moveSpeed;
	//�d��
	float gravity;
	//���[���h�ϊ��̏������s���K�v�������邩
	bool recomputeWorldTransform;
	// �����������ǂ���
	bool hitFlag;
	// ���X�|�[��������
	bool respawnFlag;
	// �����ʒu�ɖ߂���
	bool originalPosFlag;
	
	//�V�[���̃^�O
	SceneBase::Scene sceneTag;
	//�A�^�b�`����Ă���R���|�[�l���g
	std::vector<class Component*>components;
private:
	//�V�[�����ׂ��ۂɉ�������I�u�W�F�N�g���ǂ����A�J�����Ȃǂ��ΏۂɂȂ�
	bool reUseObject;
};

