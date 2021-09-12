/*
@file	PhysicsWorld.h
@brief	当たり判定を行う
*/

/*
@brief	インクルード
*/
#include "pch.h"

//自分のインスタンスの初期化
PhysicsWorld* PhysicsWorld::mPhysics = nullptr;

PhysicsWorld::PhysicsWorld()
	: mCheckPointNum(0)
	, mRangeHitsBegin(0)
	, mRangeHitsNext(0)
{
}

void PhysicsWorld::CreateInstance()
{
	if (mPhysics == nullptr)
	{
		mPhysics = new PhysicsWorld();
	}
}

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
	mRangeHitsBegin = 0;

	// 当たり判定用のデータ配列をワールド座標で手前にあるオブジェクトから順に並べていく
	std::sort(mBoxes.begin(), mBoxes.end(),[](BoxCollider* _frontBox, BoxCollider* _behindBox)
	{
		return _frontBox->GetOwner()->GetPosition().z < _behindBox->GetOwner()->GetPosition().z;
	});
}

//void PhysicsWorld::HitCheck()
//{
//	SphereAndSphere();
//    BoxAndBox();
//    SphereAndBox();
//}

void PhysicsWorld::HitCheck(BoxCollider* _box)
{
	//コライダーの親オブジェクトがActiveじゃなければ終了する
	if (_box->GetOwner()->GetState() != State::Active)
	{
		return;
	}

	for (auto itr : mSpheres)
	{
		//コライダーの親オブジェクトがActiveじゃなければ終了する
		if (itr->GetOwner()->GetState() != State::Active)
		{
			continue;
		}
		bool hit = Intersect(itr->GetWorldSphere(),_box->GetWorldBox());
		if (hit)
		{
			OnCollisionFunc func = mCollisionFunction.at(_box);
			func(*(itr->GetOwner()));
			func = mCollisionFunction.at(itr);
			func(*(_box->GetOwner()));
			_box->Refresh();
		}
	}
}

void PhysicsWorld::HitCheck(SphereCollider * _sphere)
{
	// 衝突する可能性のある範囲の要素数をカウント
	int countRangeHitsNum = 0;
	int countRangeHitsNextNum = 0;
	// 球状の当たり判定がアタッチされているオブジェクトのz座標
	float sphereZPos = _sphere->GetOwner()->GetPosition().z;

	//コライダーの親オブジェクトがActiveじゃなければ終了する
	if (_sphere->GetOwner()->GetState() != State::Active)
	{
		return;
	}

	int count = 0;

	for (unsigned int i = mRangeHitsBegin; i < mRangeHitsBegin + 10; i++)
	{

		// 矩形状の当たり判定の最大z座標
		float boxZMax = mBoxes[i]->GetWorldBox().m_max.z;
		// 矩形状の当たり判定の最小z座標
		float boxZMin = mBoxes[i]->GetWorldBox().m_min.z;

		//コライダーの親オブジェクトがActiveじゃなければ終了する
		if (mBoxes[i]->GetOwner()->GetState() != State::Active)
		{
			continue;
		}

		count++;

		/*if (mBoxes[i]->GetTag() == ColliderTag::respawn01 || mBoxes[i]->GetTag() == ColliderTag::respawn02 || mBoxes[i]->GetTag() == ColliderTag::respawn03)
		{

		}*/

		bool hit = Intersect(_sphere->GetWorldSphere(), mBoxes[i]->GetWorldBox());
		if (hit)
		{
			OnCollisionFunc func = mCollisionFunction.at(_sphere);
			func(*(mBoxes[i]->GetOwner()));
			func = mCollisionFunction.at(mBoxes[i]);
			func(*(_sphere->GetOwner()));
			_sphere->Refresh();
		}

		if (sphereZPos > boxZMin &&
			sphereZPos < boxZMax)
		{
			mRangeHitsNext = ++countRangeHitsNum;
		}
		else if (sphereZPos >= mBoxes[i + mRangeHitsNext]->GetWorldBox().m_min.z)
		{
			mRangeHitsBegin += mRangeHitsNext;
			break;
		}
		/*else if(sphereZPos >= mBoxes[i + 5]->GetWorldBox().m_min.z)
		{
			mRangeHitsBegin += mRangeHitsNext;
		}*/

		//printf("%d\n", count);

		//else if (sphereZPos + 220 >= boxZMax)
		//{/*
		//	mRangeHitsBegin += 0;*/
		//	break;
		//}
	}
}

void PhysicsWorld::AddBox(BoxCollider * _box, OnCollisionFunc _func)
{
	mBoxes.emplace_back(_box);
	//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
	mCollisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
}

void PhysicsWorld::RemoveBox(BoxCollider * _box)
{
	auto iter = std::find(mBoxes.begin(), mBoxes.end(), _box);
	if (iter != mBoxes.end())
	{
		std::iter_swap(iter, mBoxes.end() - 1);
		mBoxes.pop_back();
	}
    mCollisionFunction.erase(_box);
}

void PhysicsWorld::AddSphere(SphereCollider * _sphere, OnCollisionFunc _func)
{
	mSpheres.emplace_back(_sphere);
    //コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
    mCollisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_sphere), _func));
}

void PhysicsWorld::RemoveSphere(SphereCollider * _sphere)
{
	auto iter = std::find(mSpheres.begin(), mSpheres.end(), _sphere);
	if (iter != mSpheres.end())
	{
		std::iter_swap(iter, mSpheres.end() - 1);
		mSpheres.pop_back();
	}
    mCollisionFunction.erase(_sphere);
}

//void PhysicsWorld::SphereAndSphere()
//{
//	for (size_t i = 0; i < mSpheres.size(); i++)
//	{
//		if (mSpheres[i]->GetOwner()->GetState() != Active)
//		{
//			continue;
//		}
//		for (size_t j = i + 1; j < mSpheres.size(); j++)
//		{
//			if (mSpheres[j]->GetOwner()->GetState() != Active)
//			{
//				continue;
//			}
//			bool hit = Intersect(mSpheres[i]->GetWorldSphere(), mSpheres[j]->GetWorldSphere());
//
//			if (hit)
//			{
//				SphereCollider* sphereA = mSpheres[i];
//				SphereCollider* sphereB = mSpheres[j];
//
//				sphereA->GetOwner()->OnCollision(*(sphereB->GetOwner()));
//				sphereB->GetOwner()->OnCollision(*(sphereA->GetOwner()));
//			}
//		}
//	}
//}
//
//void PhysicsWorld::BoxAndBox()
//{
//	for (size_t i = 0; i < mBoxes.size(); i++)
//	{
//		if (mBoxes[i]->GetOwner()->GetState() != Active)
//		{
//			continue;
//		}
//		for (size_t j = i + 1; j < mBoxes.size(); j++)
//		{
//			if (mBoxes[j]->GetOwner()->GetState() != Active)
//			{
//				continue;
//			}
//			bool hit = Intersect(mBoxes[i]->GetWorldBox(), mBoxes[j]->GetWorldBox());
//
//			if (hit)
//			{
//				BoxCollider* boxA = mBoxes[i];
//				BoxCollider* boxB = mBoxes[j];
//
//				boxA->GetOwner()->OnCollision(*(boxB->GetOwner()));
//				boxB->GetOwner()->OnCollision(*(boxA->GetOwner()));
//			}
//		}
//	}
//}
//
//void PhysicsWorld::SphereAndBox()
//{
//	for (size_t i = 0; i < mSpheres.size(); i++)
//	{
//		if (mSpheres[i]->GetOwner()->GetState() != Active)
//		{
//			continue;
//		}
//		for (size_t j = 0; j < mBoxes.size(); j++)
//		{
//			if (mBoxes[j]->GetOwner()->GetState() != Active)
//			{
//				continue;
//			}
//			bool hit = Intersect(mSpheres[i]->GetWorldSphere(), mBoxes[j]->GetWorldBox());
//
//			if (hit)
//			{
//				spheres[i]->GetOwner()->OnCollision(*(boxes[j]->GetOwner()));
//				boxes[j]->GetOwner()->OnCollision(*(spheres[i]->GetOwner()));
//			}
//		}
//	}
//}

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void CalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
{
	_calcFixVec = Vector3(0, 0, 0);
	float dx1 = _fixedBox.m_min.x - _movableBox.m_max.x;
	float dx2 = _fixedBox.m_max.x - _movableBox.m_min.x;
	float dy1 = _fixedBox.m_min.y - _movableBox.m_max.y;
	float dy2 = _fixedBox.m_max.y - _movableBox.m_min.y;
	float dz1 = _fixedBox.m_min.z - _movableBox.m_max.z;
	float dz2 = _fixedBox.m_max.z - _movableBox.m_min.z;

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
