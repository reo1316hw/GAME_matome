//=============================================================================
//	@file	PhysicsWorld.h
//	@brief	当たり判定を行う
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once

#include <vector>
#include <map>
#include <functional>
#include "Math.h"
#include "Collision.h"

#define PHYSICS PhysicsWorld::GetInstance()

class Game;
class GameObject;
class BoxCollider;
class SphereCollider;
class ColliderComponent;

typedef std::function<void(GameObject&)> onCollisionFunc;
typedef std::map<ColliderComponent*, std::function<void(GameObject&)>> onCollisionMap;

class PhysicsWorld
{
public:
	static PhysicsWorld* GetInstance() { return physics; }
	static void CreateInstance();
	static void DeleteInstance();

	//当たり判定
    void HitCheck();
    void HitCheck(BoxCollider* _box);
    void HitCheck(SphereCollider* _sphere);

    void AddBox(BoxCollider* _box, onCollisionFunc _func);
    void RemoveBox(BoxCollider* _box);
	void AddSphere(SphereCollider* _sphere, onCollisionFunc _func);
	void RemoveSphere(SphereCollider* _sphere);


	void SphereAndBox();


private:
	//コンストラクタの隠蔽
	PhysicsWorld();

	static PhysicsWorld* physics;

	void SphereAndSphere();
	void BoxAndBox();

    std::vector<BoxCollider*> boxes;
	std::vector<BoxCollider*> groundBoxes;
	std::vector<BoxCollider*> glassBoxes;
	std::vector<BoxCollider*> blockBoxes;
	std::vector<BoxCollider*> verticalMoveGroundBoxes;
	std::vector<BoxCollider*> jumpBoxes;
	std::vector<BoxCollider*> lateralMoveGroundBoxes;
	std::vector<BoxCollider*> playerBoxes;
	std::vector<BoxCollider*> upBlockBoxes;
	std::vector<BoxCollider*> upBlock_02Boxes;
	std::vector<BoxCollider*> verticalBlockBoxes;
	std::vector<BoxCollider*> aerialBlockBoxes;
	std::vector<BoxCollider*> rightBlockBoxes;
	std::vector<BoxCollider*> leftBlockBoxes;
	std::vector<BoxCollider*> rightOneBlockBoxes;
	std::vector<BoxCollider*> rightOneBlock_02Boxes;
	std::vector<BoxCollider*> leftOneBlockBoxes;
	std::vector<BoxCollider*> leftOneBlock_02Boxes;
	std::vector<BoxCollider*> downBlockBoxes;
	std::vector<BoxCollider*> goalBlockBoxes;
	std::vector<BoxCollider*> respawn01Boxes;
	std::vector<BoxCollider*> respawn02Boxes;
	std::vector<BoxCollider*> respawn03Boxes;
	std::vector<SphereCollider*> spheres;
	std::vector<SphereCollider*> playerSpheres;
	onCollisionMap collisionFunction;

};

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);
