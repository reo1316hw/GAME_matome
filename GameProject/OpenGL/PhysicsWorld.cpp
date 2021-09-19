/*
@file  PhysicsWorld.h
@brief 当たり判定を行う
*/

/*
@brief インクルード
*/
#include "pch.h"

//自分のインスタンスの初期化
PhysicsWorld* PhysicsWorld::mPhysics = nullptr;

/*
@fn	コンストラクタの隠蔽
*/
PhysicsWorld::PhysicsWorld()
	: mRespawnNum(0)
	, mHitRangeBegin(0)
	, mHitRangeCount(0)
	, mCountHitRangeNum(0)
	, mSphereZPos(0)
	, mRespawnZPos(0)
	, mNextSphereZPos(0)
	, mRespawnFlag(false)
{
}

/*
@fn	インスタンスを作成する
*/
void PhysicsWorld::CreateInstance()
{
	if (mPhysics == nullptr)
	{
		mPhysics = new PhysicsWorld();
	}
}

/*
@fn	インスタンスを削除する
*/
void PhysicsWorld::DeleteInstance()
{
	if (mPhysics != nullptr)
	{
		delete mPhysics;
		mPhysics = nullptr;
	}
}

/*
@fn 初期化
*/
void PhysicsWorld::Initialize()
{
	mHitRangeBegin = 0;

	// 当たり判定用のデータ配列をワールド座標で手前にあるオブジェクトから順に並べていく
	std::sort(mBoxes.begin(), mBoxes.end(), [](BoxCollider* _frontBox, BoxCollider* _behindBox)
		{
			return _frontBox->GetOwner()->GetPosition().z < _behindBox->GetOwner()->GetPosition().z;
		});
}

/*
@fn		矩形の当たり判定
@brief	矩形の当たり判定がどのオブジェクトと当たったかタグで調べる
@param _box BoxColliderクラスのポインタ
*/
void PhysicsWorld::HitCheck(BoxCollider* _box)
{
	//コライダーの親オブジェクトがActiveじゃなければ終了する
	if (_box->GetOwner()->GetState() != State::eActive)
	{
		return;
	}

	for (auto itr : mSpheres)
	{
		//コライダーの親オブジェクトがActiveじゃなければ終了する
		if (itr->GetOwner()->GetState() != State::eActive)
		{
			continue;
		}

		//sphereと当たったか
		bool hit = Intersect(itr->GetWorldSphere(), _box->GetWorldBox());
		if (hit)
		{
			//sphereの当たった際のリアクション処理
			OnCollisionFunc func = mCollisionFunction.at(_box);
			func(*(itr->GetOwner()));
			func = mCollisionFunction.at(itr);
			func(*(_box->GetOwner()));
			_box->Refresh();
		}
	}
}

/*
@fn		球の当たり判定
@brief	球の当たり判定がどのオブジェクトと当たったかタグで調べる
@param _sphere SphereColliderクラスのポインタ
*/
void PhysicsWorld::HitCheck(SphereCollider* _sphere)
{
	//衝突する可能性のある範囲を指定する数
	const int DecideHitRange = 20;

	//衝突する可能性のある範囲
	int hitRange = mHitRangeBegin + DecideHitRange;

	//球状の当たり判定がアタッチされているオブジェクトのz速度
	float sphereZVel = _sphere->GetOwner()->GetVelocity().z;

	mCountHitRangeNum = 0;
	mSphereZPos = _sphere->GetOwner()->GetPosition().z;
	mRespawnZPos = _sphere->GetOwner()->GetRespawnPos().z;
    mRespawnFlag = _sphere->GetOwner()->GetRespawnFlag();
	mNextSphereZPos = mSphereZPos + sphereZVel;

	//コライダーの親オブジェクトがActiveじゃなければ終了する
	if (_sphere->GetOwner()->GetState() != State::eActive)
	{
		return;
	}

	//プレイヤーの最小z座標から前方20個の範囲だけで当たり判定処理を行う
	for (int i = mHitRangeBegin; i < hitRange; i++)
	{
		hitRange = mHitRangeBegin + DecideHitRange;

		//カウントが配列の範囲から超えたらループから抜ける
		if (i == mBoxes.size())
		{
			break;
		}

		//コライダーの親オブジェクトがActiveじゃなければ終了する
		if (mBoxes[i]->GetOwner()->GetState() != State::eActive)
		{
			continue;
		}

		//boxと当たったか
		bool hit = Intersect(_sphere->GetWorldSphere(), mBoxes[i]->GetWorldBox());
		if (hit)
		{
			//boxの当たった際のリアクション処理
			OnCollisionFunc func = mCollisionFunction.at(_sphere);
			func(*(mBoxes[i]->GetOwner()));
			func = mCollisionFunction.at(mBoxes[i]);
			func(*(_sphere->GetOwner()));
			_sphere->Refresh();
		}

		//リスポーン通過時の要素番号を検索
		SearchRespawnNum();

		//当たる範囲の最初の番号を増加させる
		if (IncrementHitRange(i))
		{
			break;
		}
	}
}

/*
@fn	リスポーン通過時の要素番号を検索
*/
void PhysicsWorld::SearchRespawnNum()
{
	//リスポーン地点を最大最小の座標にずらすための数
	const float ShiftPos = 100.0f;

	//リスポーン地点の最大z座標
	float respawnZMax = mRespawnZPos + ShiftPos;
	//リスポーン地点の最小z座標
	float respawnZMin = mRespawnZPos - ShiftPos;

	if (mRespawnFlag)
	{
		mHitRangeBegin = mRespawnNum;
		mHitRangeCount = 0;
	}
	else if (mNextSphereZPos >= respawnZMin &&
		     mNextSphereZPos <= respawnZMax)
	{
		mRespawnNum = mHitRangeBegin;
	}
}

/*
@fn	当たる範囲の最初の番号を増加させる
@param _num 番号
@return true : 検索終了 , false : 検索続行
*/
bool PhysicsWorld::IncrementHitRange(const int _num)
{
	//矩形状の当たり判定の最大z座標
	float boxZMax = mBoxes[_num]->GetWorldBox().m_max.z;
	//矩形状の当たり判定の最小z座標
	float boxZMin = mBoxes[_num]->GetWorldBox().m_min.z;
	//矩形状の当たり判定がアタッチされているオブジェクトの初期座標から移動した距離の差
	float boxZdif = abs(mBoxes[_num]->GetOwner()->GetInitPosition().z - mBoxes[_num]->GetOwner()->GetPosition().z);
	// 矩形状の当たり判定の最大初期z座標
	float boxInitZMax = boxZMax - boxZdif;
	// 矩形状の当たり判定の最小初期z座標
	float boxInitZMin = boxZMin - boxZdif;

	if (mSphereZPos >= boxInitZMin &&
		mSphereZPos <= boxInitZMax)
	{
		mHitRangeCount = ++mCountHitRangeNum;
	}
	else if (mNextSphereZPos >= boxInitZMin)
	{
		mHitRangeBegin += mHitRangeCount;

		if (mCountHitRangeNum == 0)
		{
			mHitRangeCount = 0;
		}

		return true;
	}

	return false;
}

/*
@fn		矩形の当たり判定を追加
@param	_box　追加するBoxColliderクラスのポインタ
*/
void PhysicsWorld::AddBox(BoxCollider* _box, OnCollisionFunc _func)
{
	mBoxes.emplace_back(_box);
	//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
	mCollisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
}

/*
@fn		矩形の当たり判定を削除
@param	_box　削除するBoxColliderクラスのポインタ
*/
void PhysicsWorld::RemoveBox(BoxCollider* _box)
{
	auto iter = std::find(mBoxes.begin(), mBoxes.end(), _box);
	if (iter != mBoxes.end())
	{
		std::iter_swap(iter, mBoxes.end() - 1);
		mBoxes.pop_back();
	}
	mCollisionFunction.erase(_box);
}

/*
@fn		球の当たり判定を追加
@param	_sphere　追加するSphereColliderクラスのポインタ
*/
void PhysicsWorld::AddSphere(SphereCollider* _sphere, OnCollisionFunc _func)
{
	mSpheres.emplace_back(_sphere);
	//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
	mCollisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_sphere), _func));
}

/*
@fn		球の当たり判定を削除
@param	_sphere　削除するSphereColliderクラスのポインタ
*/
void PhysicsWorld::RemoveSphere(SphereCollider* _sphere)
{
	auto iter = std::find(mSpheres.begin(), mSpheres.end(), _sphere);
	if (iter != mSpheres.end())
	{
		std::iter_swap(iter, mSpheres.end() - 1);
		mSpheres.pop_back();
	}
	mCollisionFunction.erase(_sphere);
}

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _MovableBox 移動物体
@param _FixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void CalcCollisionFixVec(const AABB& _MovableBox, const AABB& _FixedBox, Vector3& _calcFixVec)
{
	_calcFixVec = Vector3(0, 0, 0);
	float dx1 = _FixedBox.m_min.x - _MovableBox.m_max.x;
	float dx2 = _FixedBox.m_max.x - _MovableBox.m_min.x;
	float dy1 = _FixedBox.m_min.y - _MovableBox.m_max.y;
	float dy2 = _FixedBox.m_max.y - _MovableBox.m_min.y;
	float dz1 = _FixedBox.m_min.z - _MovableBox.m_max.z;
	float dz2 = _FixedBox.m_max.z - _MovableBox.m_min.z;

	// dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;

	// x, y, zのうち最も差が小さい軸で位置を調整
	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		_calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		_calcFixVec.y = dy;
	}
	else
	{
		_calcFixVec.z = dz;
	}

}
