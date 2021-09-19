/*
@file  PhysicsWorld.h
@brief 当たり判定を行う
*/

/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class Game;
class GameObject;
class BoxCollider;
class SphereCollider;
class ColliderComponent;
class Player;

#define PHYSICS PhysicsWorld::GetInstance()
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
	@fn 初期化
	*/
	void Initialize();

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

	/*
    @fn	リスポーン通過時の要素番号を検索
    */
	void SearchRespawnNum();

	/*
    @fn	当たる範囲の最初の番号を増加させる
	@param _num 番号
	@return true : 検索終了 , false : 検索続行
    */
	bool IncrementHitRange(const int _num);

	//自分のインスタンス
	static PhysicsWorld* mPhysics;

	// 矩形の当たり判定を全て格納するための可変長コンテナ
    std::vector<BoxCollider*> mBoxes;
	// 球の当たり判定を全て格納するための可変長コンテナ
	std::vector<SphereCollider*> mSpheres;

	// 衝突する可能性のある範囲の最初の番号
	int mHitRangeBegin;
	// 衝突する可能性のある範囲にどれだけオブジェクトがあるか
	int mHitRangeCount;
	// リスポーン通過時の要素番号
	int mRespawnNum;
	//衝突する可能性のある範囲の要素数をカウント
	int mCountHitRangeNum ;

	//球状の当たり判定がアタッチされているオブジェクトのz座標
	float mSphereZPos;
	//リスポーンZ地点
	float mRespawnZPos;
	//球状の当たり判定がアタッチされている次のフレームのオブジェクトのz座標
	float mNextSphereZPos;

	//リスポーンしたか
	bool  mRespawnFlag;

	OnCollisionMap mCollisionFunction;

public://ゲッターセッター

	/*
	@return PhysicsWorldクラスのインスタンス(PhysicsWorld型)
	*/
	static PhysicsWorld* GetInstance() { return mPhysics; }
};

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _MovableBox 移動物体
@param _FixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void CalcCollisionFixVec(const AABB& _MovableBox, const AABB& _FixedBox, Vector3& _calcFixVec);