//=============================================================================
//	@file	ColliderComponent.h
//	@brief	当たり判定を行うコンポーネントの規定クラス
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	プリプロセッサ
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Component.h"
#include "Collision.h"
//#include "GameObject.h"

//-----------------------------------------------------------------------------
//	@brief	前方宣言
//-----------------------------------------------------------------------------
class GameObject;

/*
	@enum　GameObjectタグ
	衝突相手を判別するために使用
	*/
enum class ColliderTag
{
	OtherTag = 0,
	CameraTag = 1,
	playerTag = 2,
	groundTag = 3,
	glassTag = 4,
	blockTag = 5,
	verticalMoveGroundTag = 6,
	jumpTag = 7,
	lateralMoveGroundTag = 8,
	upBlockTag = 9,
	upBlock_02Tag = 10,
	verticalBlockTag = 11,
	aerialBlockTag = 12,
	rightBlockTag = 13,
	leftBlockTag = 14,
	rightOneBlockTag = 15,
	rightOneBlock_02Tag = 16,
	leftOneBlockTag = 17,
	leftOneBlock_02Tag = 18,
	downBlockTag = 19,
	goalBlockTag = 20,
	isGroundtag = 21,
	respawn01 = 22,
	respawn02 = 23,
	respawn03 = 24,
	SwithTag = 25
};

//-----------------------------------------------------------------------------
//	@brief	ColliderComponentクラス
//-----------------------------------------------------------------------------
class ColliderComponent : public Component
{
public:
//===================== publicのメンバ関数 ======================//

    /**
	@brief	コンストラクタ
	@param	アタッチするゲームオブジェクトのポインタ
    @param	コンポーネントの更新順番（数値が小さいほど早く更新される）
    @param  当たり判定時に、めり込みから動かす処理の優先度を決める数値
    */
	ColliderComponent(GameObject* _owner, ColliderTag _tag, int _updateOrder = 200,int _collisionOrder = 100);

	/**
	@brief	めり込み動かす際の優先度を示す数値を取得する
	@return 優先度を示す数値(int)
	*/
	int GetCollisionOrder() const { return collisionOrder; }

	ColliderTag GetTag() const { return mTag; };

	//未実装
	////オブジェクトが球に当たった時にめりこみからずらす処理
	//virtual void ShiftObject(const Sphere& _hirSphere) {}
	////オブジェクトが平面に当たった時にめりこみからずらす処理
	//virtual void ShiftObject(const Plane& _hitPlane) {}
	////オブジェクトがAABBに当たった時にめりこみからずらす処理
	//virtual void ShiftObject(const AABB& _hitBox) {}
	////オブジェクトがカプセルに当たった時にめりこみからずらす処理
	//virtual void ShiftObject(const Capsule& _hitCapsule) {}

protected:
	ColliderTag mTag;

private:
//===================== privateのメンバ変数 ======================//

	bool isTrigger;			//実体を伴う当たり判定をするかどうか
	int	 collisionOrder;	//数値が大きい方を優先してめり込みから動かす処理をする（0以下は動かさない）
};

