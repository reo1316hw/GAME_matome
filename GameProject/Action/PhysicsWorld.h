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

	//自分のインスタンス
	static PhysicsWorld* mPhysics;

	/*
	@fn	矩形と矩形の当たり判定
	*/
	void BoxAndBox();

	/*
	@fn	球と球の当たり判定
	*/
	void SphereAndSphere();

	/*
	@fn	球と矩形の当たり判定
	*/
	void SphereAndBox();

	//矩形の当たり判定を全て格納するための可変長コンテナ
    std::vector<BoxCollider*> mBoxes;

	//床の矩形当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mGroundBoxes;
	//ガラス床の矩形当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mGlassBoxes;
	//障害物の矩形当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mBlockBoxes;
	//縦移動床の矩形当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mVerticalMoveGroundBoxes;
	//ジャンプ床の矩形当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mJumpBoxes;
	//横移動床の矩形当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mLateralMoveGroundBoxes;
	//上移動ブロックの矩形当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mUpBlockBoxes;
	std::vector<BoxCollider*> mUpBlock_02Boxes;
	//縦長障害物の矩形当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mVerticalBlockBoxes;
	//空中ブロックの矩形当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mAerialBlockBoxes;
	//右移動ブロックの矩形当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mRightBlockBoxes;
	//左移動ブロックの矩形当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mLeftBlockBoxes;
	//1マス右移動床の矩形当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mRightOneBlockBoxes;
	std::vector<BoxCollider*> mRightOneBlock_02Boxes;
	//1マス右移動床の矩形当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mLeftOneBlockBoxes;
	std::vector<BoxCollider*> mLeftOneBlock_02Boxes;
	//落ちるブロックの矩形当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mDownBlockBoxes;
	//ゴール柱の矩形当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mGoalBlockBoxes;
	//リスポーン地点の矩形当たり判定を全て格納するための可変長コンテナ
	std::vector<BoxCollider*> mRespawn01Boxes;
	std::vector<BoxCollider*> mRespawn02Boxes;
	std::vector<BoxCollider*> mRespawn03Boxes;

	//球の当たり判定を全て格納するための可変長コンテナ
	std::vector<SphereCollider*> mSpheres;
	//プレイヤーの球当たり判定を全て格納するための可変長コンテナ
	std::vector<SphereCollider*> mPlayerSpheres;

	OnCollisionMap mCollisionFunction;

public://ゲッターセッター

	/*
	@return PhysicsWorldクラスのインスタンス(PhysicsWorld型)
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