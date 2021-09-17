/*
@file  ColliderComponent.h
@brief 当たり判定を行うコンポーネントの規定クラス
*/

/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief インクルード
*/
#include "Component.h"
#include "Collision.h"

/*
@brief 前方宣言
*/
class GameObject;

/*
@enum　GameObjectタグ
衝突相手を判別するために使用
*/
enum class ColliderTag
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
	eUpBlockTag = 9,
	eUpBlock_02Tag = 10,
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
	eIsGroundtag = 21,
	eCheckpoint = 22,
	eSwithTag = 23
};

class ColliderComponent : public Component
{
public:

    /*
	@fn		コンストラクタ
	@param	_owner アタッチするゲームオブジェクトのポインタ
	@param	_tag アタッチするゲームオブジェクトの当たり判定のタグ
    @param	_updateOrder コンポーネントの更新順番（数値が小さいほど早く更新される）
    @param  _collisionOrder 当たり判定時に、めり込みから動かす処理の優先度を決める数値
    */
	ColliderComponent(GameObject* _owner, ColliderTag _tag, int _updateOrder = 200,int _collisionOrder = 100);

protected:

	//アタッチするゲームオブジェクトの当たり判定のタグ
	ColliderTag mTag;

private:

	//実体を伴う当たり判定をするかどうか
	bool mTriggerFlag;
	//数値が大きい方を優先してめり込みから動かす処理をする（0以下は動かさない）
	int	 mCollisionOrder;

public: //ゲッターセッター

	/*
	@fn		めり込み動かす際の優先度を示す数値を取得する
	@return 優先度を示す数値(int型)
	*/
	int GetCollisionOrder() const { return mCollisionOrder; }

	/*
	@fn		アタッチするゲームオブジェクトの当たり判定のタグを取得する
	@return	タグの番号(enum型 ColliderTag)
	*/
	ColliderTag GetTag() const { return mTag; };
};

