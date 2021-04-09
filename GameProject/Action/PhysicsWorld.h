/*
@file	PhysicsWorld.h
@brief	当たり判定を行う
*/

/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/
#include <map>
#include <functional>
#include "Collision.h"

#define PHYSICS PhysicsWorld::GetInstance()

class Game;
class GameObject;
class BoxCollider;
class SphereCollider;
class ColliderComponent;

typedef std::function<void(GameObject&)> OnCollisionFunc;
typedef std::map<ColliderComponent*, std::function<void(GameObject&)>> OnCollisionMap;

class PhysicsWorld
{
public:

	/*
	@fn	インスタンスを作成する
	*/
	static void CreateInstance();

	/*
	@fn	インスタンスを削除する
	*/
	static void DeleteInstance();

	/*
	@fn	当たり判定
	*/
    void HitCheck();

	/*
	@fn		矩形の当たり判定
	@brief	矩形の当たり判定がどのオブジェクトと当たったかタグで調べる
	@param _box BoxColliderクラスのポインタ
	*/
    void HitCheck(BoxCollider* _box);

	/*
	@fn		球の当たり判定
	@brief	球の当たり判定がどのオブジェクトと当たったかタグで調べる
	@param _sphere SphereColliderクラスのポインタ
	*/
    void HitCheck(SphereCollider* _sphere);

	/*
	@fn		矩形の当たり判定を追加
	@param	_box　追加するBoxColliderクラスのポインタ
	*/
    void AddBox(BoxCollider* _box, OnCollisionFunc _func);

	/*
	@fn		矩形の当たり判定を削除
	@param	_box　削除するBoxColliderクラスのポインタ
	*/
    void RemoveBox(BoxCollider* _box);

	/*
	@fn		球の当たり判定を追加
	@param	_sphere　追加するSphereColliderクラスのポインタ
	*/
	void AddSphere(SphereCollider* _sphere, OnCollisionFunc _func);

	/*
	@fn		球の当たり判定を削除
	@param	_sphere　削除するSphereColliderクラスのポインタ
	*/
	void RemoveSphere(SphereCollider* _sphere);

private:

	/*
	@fn	コンストラクタの隠蔽
	*/
	PhysicsWorld();

	static PhysicsWorld* mPhysics;

	void BoxAndBox();
	void SphereAndSphere();
	void SphereAndBox();

    std::vector<BoxCollider*> mBoxes;
	std::vector<BoxCollider*> mGroundBoxes;
	std::vector<BoxCollider*> mGlassBoxes;
	std::vector<BoxCollider*> mBlockBoxes;
	std::vector<BoxCollider*> mVerticalMoveGroundBoxes;
	std::vector<BoxCollider*> mJumpBoxes;
	std::vector<BoxCollider*> mLateralMoveGroundBoxes;
	std::vector<BoxCollider*> mPlayerBoxes;
	std::vector<BoxCollider*> mUpBlockBoxes;
	std::vector<BoxCollider*> mUpBlock_02Boxes;
	std::vector<BoxCollider*> mVerticalBlockBoxes;
	std::vector<BoxCollider*> mAerialBlockBoxes;
	std::vector<BoxCollider*> mRightBlockBoxes;
	std::vector<BoxCollider*> mLeftBlockBoxes;
	std::vector<BoxCollider*> mRightOneBlockBoxes;
	std::vector<BoxCollider*> mRightOneBlock_02Boxes;
	std::vector<BoxCollider*> mLeftOneBlockBoxes;
	std::vector<BoxCollider*> mLeftOneBlock_02Boxes;
	std::vector<BoxCollider*> mDownBlockBoxes;
	std::vector<BoxCollider*> mGoalBlockBoxes;
	std::vector<BoxCollider*> mRespawn01Boxes;
	std::vector<BoxCollider*> mRespawn02Boxes;
	std::vector<BoxCollider*> mRespawn03Boxes;
	std::vector<SphereCollider*> mSpheres;
	std::vector<SphereCollider*> mPlayerSpheres;

	OnCollisionMap mCollisionFunction;

public://ゲッターセッター

	/*
	@return PhysicsWorldクラスのインスタンス
	*/
	static PhysicsWorld* GetInstance() { return mPhysics; }
};

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void CalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);
