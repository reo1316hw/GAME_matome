//=============================================================================
//	@file	SphereCollider.h
//	@brief	球の当たり判定を行うコンポーネント
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	プリプロセッサ
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ColliderComponent.h"
#include "PhysicsWorld.h"

//-----------------------------------------------------------------------------
//	@brief	SphereColliderクラス
//-----------------------------------------------------------------------------
class SphereCollider final : public ColliderComponent
{
public:
//===================== publicのメンバ関数 ======================//

	/*
	@fn		コンストラクタ
	@param	アタッチするゲームオブジェクトのポインタ
	@param	他のオブジェクトと当たった時に呼ばれる関数ポインタ(GetOnCollisionFuncを呼ぶ)
	@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
	@param	当たり判定時に、めり込みから動かす処理の優先度を決める数値
	*/
	SphereCollider(GameObject* _owner, ColliderTag _tag, onCollisionFunc _func, int _updateOrder = 200, int _collisionOrder = 100);

	/*
	@fn	デストラクタ
	*/
	virtual ~SphereCollider();

	/*
	@fn	Transformのワールド変換
	*/
	void OnUpdateWorldTransform() override;

	/*
	@fn		ヒットしたオブジェクトが二つ以上あった場合、どのオブジェクトと押し戻しをするか
			タグで調べた後にまたTransformのワールド変換をする
	@detail ヒットしたオブジェクト二つの間にいた場合、引っかかったり、すり抜けするので
			それを防ぐためにもう一度Transformのワールド変換をする
	*/
	void Refresh() override;
private:
//===================== privateのメンバ変数 ======================//

	//オブジェクトに設定する用の球（中心をオブジェクトの中心にする）
	Sphere mObjectSphere;
	//当たり判定するときに使う球（中心をワールド座標の中心にする）
	Sphere mWorldSphere;
public: //ゲッターセッター
	/*
	@fn		当たり判定時に使うワールド空間でのSphereを取得する
	@return 中心をワールド座標に合わせたSphereの構造体
	*/
	Sphere GetWorldSphere() const { return mWorldSphere; }

	/*
	@fn		当たり判定に使うSphereの設定
	@param	オブジェクトの大きさに合わせたSphereの構造体
	*/
	void SetObjectSphere(const Sphere& _sphere) { mObjectSphere = _sphere; }
};

