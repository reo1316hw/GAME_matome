//=============================================================================
//	@file	PhysicsWorld.cpp
//	@brief	当たり判定を行う
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#include "PhysicsWorld.h"
#include <algorithm>
#include <SDL.h>
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "ColliderComponent.h"

PhysicsWorld* PhysicsWorld::physics = nullptr;

PhysicsWorld::PhysicsWorld()
{
}

void PhysicsWorld::CreateInstance()
{
	if (physics == nullptr)
	{
		physics = new PhysicsWorld();
	}
}

void PhysicsWorld::DeleteInstance()
{
	if (physics != nullptr)
	{
		delete physics;
		physics = nullptr;
	}
}

void PhysicsWorld::HitCheck()
{
	SphereAndSphere();
    BoxAndBox();
    SphereAndBox();
}

void PhysicsWorld::HitCheck(BoxCollider* _box)
{
	//コライダーの親オブジェクトがActiveじゃなければ終了する
	if (_box->GetOwner()->GetState() != State::Active)
	{
		return;
	}

	//if (_box->GetTag() == ColliderComponent::playerTag)
	//{
	//	for (auto itr : groundBoxes)
	//	{
	//		if (itr == _box)
	//		{
 //				continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する 
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
 // 			bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{	
 //				onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);          
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//	for (auto itr : glassBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//	for (auto itr : blockBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//	for (auto itr : verticalMoveGroundBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//	for (auto itr : jumpBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//	for (auto itr : lateralMoveGroundBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//	for (auto itr : upBlockBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//	for (auto itr : upBlock_02Boxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//	for (auto itr : verticalBlockBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//	for (auto itr : aerialBlockBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//	for (auto itr : rightBlockBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//	for (auto itr : leftBlockBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//	for (auto itr : rightOneBlockBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//	for (auto itr : rightOneBlock_02Boxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//	for (auto itr : leftOneBlockBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//	for (auto itr : leftOneBlock_02Boxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//	for (auto itr : downBlockBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}

	//	for (auto itr : goalBlockBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//}

	//if (_box->GetTag() == ColliderComponent::glassTag)
	//{
	//	for (auto itr : playerBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		////コライダーの親オブジェクトがActiveじゃなければ終了する
	//		//if (itr->GetOwner()->GetState() != State::Active)
	//		//{
	//		//	continue;
	//		//}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//}

	//if (_box->GetTag() == ColliderComponent::verticalMoveGroundTag)
	//{
	//	for (auto itr : playerBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		////コライダーの親オブジェクトがActiveじゃなければ終了する
	//		//if (itr->GetOwner()->GetState() != State::Active)
	//		//{
	//		//	continue;
	//		//}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//}

	//if (_box->GetTag() == ColliderComponent::rightOneBlockTag)
	//{
	//	for (auto itr : playerBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		////コライダーの親オブジェクトがActiveじゃなければ終了する
	//		//if (itr->GetOwner()->GetState() != State::Active)
	//		//{
	//		//	continue;
	//		//}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//}

	//if (_box->GetTag() == ColliderComponent::leftOneBlockTag)
	//{
	//	for (auto itr : playerBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		////コライダーの親オブジェクトがActiveじゃなければ終了する
	//		//if (itr->GetOwner()->GetState() != State::Active)
	//		//{
	//		//	continue;
	//		//}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//}

	for (auto itr : spheres)
	{
		////コライダーの親オブジェクトがActiveじゃなければ終了する
		//if (itr->GetOwner()->GetState() != State::Active)
		//{
		//	continue;
		//}
		bool hit = Intersect(itr->GetWorldSphere(),_box->GetWorldBox());
		if (hit)
		{
			onCollisionFunc func = collisionFunction.at(_box);
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_box->GetOwner()));
			_box->refresh();
		}
	}
}

void PhysicsWorld::HitCheck(SphereCollider * _sphere)
{
	//コライダーの親オブジェクトがActiveじゃなければ終了する
	if (_sphere->GetOwner()->GetState() != State::Active)
	{
		return;
	}

	if (_sphere->GetTag() == ColliderTag::playerTag)
	{
		for (auto itr : groundBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する 
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : glassBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : blockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : verticalMoveGroundBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : jumpBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : lateralMoveGroundBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : upBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : upBlock_02Boxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : verticalBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : aerialBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : rightBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : leftBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : rightOneBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : rightOneBlock_02Boxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : leftOneBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : leftOneBlock_02Boxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : downBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}

		for (auto itr : goalBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}

		for (auto itr : respawn01Boxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}

		for (auto itr : respawn02Boxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}

		for (auto itr : respawn03Boxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
	}

	if (_sphere->GetTag() == ColliderTag::isGroundtag)
	{
		for (auto itr : groundBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する 
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : glassBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : blockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : verticalMoveGroundBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : jumpBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : lateralMoveGroundBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : upBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : upBlock_02Boxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : verticalBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : aerialBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : rightBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : leftBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : rightOneBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : rightOneBlock_02Boxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : leftOneBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : leftOneBlock_02Boxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
		for (auto itr : downBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}

		for (auto itr : goalBlockBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_sphere);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_sphere->GetOwner()));
				_sphere->refresh();
			}
		}
	}

	//if (_box->GetTag() == ColliderComponent::glassTag)
	//{
	//	for (auto itr : playerBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		////コライダーの親オブジェクトがActiveじゃなければ終了する
	//		//if (itr->GetOwner()->GetState() != State::Active)
	//		//{
	//		//	continue;
	//		//}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//}

	//if (_box->GetTag() == ColliderComponent::verticalMoveGroundTag)
	//{
	//	for (auto itr : playerBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		////コライダーの親オブジェクトがActiveじゃなければ終了する
	//		//if (itr->GetOwner()->GetState() != State::Active)
	//		//{
	//		//	continue;
	//		//}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//}

	//if (_box->GetTag() == ColliderComponent::rightOneBlockTag)
	//{
	//	for (auto itr : playerBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		////コライダーの親オブジェクトがActiveじゃなければ終了する
	//		//if (itr->GetOwner()->GetState() != State::Active)
	//		//{
	//		//	continue;
	//		//}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//}

	//if (_box->GetTag() == ColliderComponent::leftOneBlockTag)
	//{
	//	for (auto itr : playerBoxes)
	//	{
	//		if (itr == _box)
	//		{
	//			continue;
	//		}
	//		////コライダーの親オブジェクトがActiveじゃなければ終了する
	//		//if (itr->GetOwner()->GetState() != State::Active)
	//		//{
	//		//	continue;
	//		//}
	//		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_box);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_box->GetOwner()));
	//			_box->refresh();
	//		}
	//	}
	//}
	for (auto itr : spheres)
	{
		if (itr == _sphere)
		{
			continue;
		}
		//コライダーの親オブジェクトがActiveじゃなければ終了する
		if (itr->GetOwner()->GetState() != State::Active)
		{
			continue;
		}
		bool hit = Intersect(itr->GetWorldSphere(), _sphere->GetWorldSphere());
		if (hit)
		{
			onCollisionFunc func = collisionFunction.at(_sphere);
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_sphere->GetOwner()));
			/*_sphere->refresh();*/
		}
	}
	for (auto itr : boxes)
	{
		//コライダーの親オブジェクトがActiveじゃなければ終了する
		if (itr->GetOwner()->GetState() != State::Active)
		{
			continue;
		}
		bool hit = Intersect(_sphere->GetWorldSphere(),itr->GetWorldBox());
		if (hit)
		{
			onCollisionFunc func = collisionFunction.at(_sphere);
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_sphere->GetOwner()));
			/*_sphere->refresh();*/
		}
	}
}

void PhysicsWorld::AddBox(BoxCollider * _box, onCollisionFunc _func)
{
	if (_box->GetTag() == ColliderTag::groundTag)
	{
		groundBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::glassTag)
	{
		glassBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::blockTag)
	{
		blockBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::verticalMoveGroundTag)
	{
		verticalMoveGroundBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::jumpTag)
	{
		jumpBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::lateralMoveGroundTag)
	{
		lateralMoveGroundBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::playerTag)
	{
		playerBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::upBlockTag)
	{
		upBlockBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::upBlock_02Tag)
	{
		upBlock_02Boxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::verticalBlockTag)
	{
		verticalBlockBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::aerialBlockTag)
	{
		aerialBlockBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::rightBlockTag)
	{
		rightBlockBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::leftBlockTag)
	{
		leftBlockBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::rightOneBlockTag)
	{
		rightOneBlockBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::rightOneBlock_02Tag)
	{
		rightOneBlock_02Boxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::leftOneBlockTag)
	{
		leftOneBlockBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::leftOneBlock_02Tag)
	{
		leftOneBlock_02Boxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::downBlockTag)
	{
		downBlockBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::goalBlockTag)
	{
		goalBlockBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::respawn01)
	{
		respawn01Boxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::respawn02)
	{
		respawn02Boxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::respawn03)
	{
		respawn03Boxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
}

void PhysicsWorld::RemoveBox(BoxCollider * _box)
{

	auto groundBox = std::find(groundBoxes.begin(), groundBoxes.end(), _box);
	if (groundBox != groundBoxes.end())
	{
		std::iter_swap(groundBox, groundBoxes.end() - 1);
		groundBoxes.pop_back();
	}
	auto glassBox = std::find(glassBoxes.begin(), glassBoxes.end(), _box);
	if (glassBox != glassBoxes.end())
	{
		std::iter_swap(glassBox, glassBoxes.end() - 1);
		glassBoxes.pop_back();
	}
	auto blockBox = std::find(blockBoxes.begin(), blockBoxes.end(), _box);
	if (blockBox != blockBoxes.end())
	{
		std::iter_swap(blockBox, blockBoxes.end() - 1);
		blockBoxes.pop_back();
	}
	auto verticalMoveGroundBox = std::find(verticalMoveGroundBoxes.begin(), verticalMoveGroundBoxes.end(), _box);
	if (verticalMoveGroundBox != verticalMoveGroundBoxes.end())
	{
		std::iter_swap(verticalMoveGroundBox, verticalMoveGroundBoxes.end() - 1);
		verticalMoveGroundBoxes.pop_back();
	}
	auto jumpBox = std::find(jumpBoxes.begin(), jumpBoxes.end(), _box);
	if (jumpBox != jumpBoxes.end())
	{
		std::iter_swap(jumpBox, jumpBoxes.end() - 1);
		jumpBoxes.pop_back();
	}
	auto lateralMoveGroundBox = std::find(lateralMoveGroundBoxes.begin(), lateralMoveGroundBoxes.end(), _box);
	if (lateralMoveGroundBox != lateralMoveGroundBoxes.end())
	{
		std::iter_swap(lateralMoveGroundBox, lateralMoveGroundBoxes.end() - 1);
		lateralMoveGroundBoxes.pop_back();
	}
	auto playerBox = std::find(playerBoxes.begin(), playerBoxes.end(), _box);
	if (playerBox != playerBoxes.end())
	{
		std::iter_swap(playerBox, playerBoxes.end() - 1);
		playerBoxes.pop_back();
	}
	auto upBlockBox = std::find(upBlockBoxes.begin(), upBlockBoxes.end(), _box);
	if (upBlockBox != upBlockBoxes.end())
	{
		std::iter_swap(upBlockBox, upBlockBoxes.end() - 1);
		upBlockBoxes.pop_back();
	}
	auto upBlock_02Box = std::find(upBlock_02Boxes.begin(), upBlock_02Boxes.end(), _box);
	if (upBlock_02Box != upBlock_02Boxes.end())
	{
		std::iter_swap(upBlock_02Box, upBlock_02Boxes.end() - 1);
		upBlock_02Boxes.pop_back();
	}
	auto verticalBlockBox = std::find(verticalBlockBoxes.begin(), verticalBlockBoxes.end(), _box);
	if (verticalBlockBox != verticalBlockBoxes.end())
	{
		std::iter_swap(verticalBlockBox, verticalBlockBoxes.end() - 1);
		verticalBlockBoxes.pop_back();
	}
	auto aerialBlockBox = std::find(aerialBlockBoxes.begin(), aerialBlockBoxes.end(), _box);
	if (aerialBlockBox != aerialBlockBoxes.end())
	{
		std::iter_swap(aerialBlockBox, aerialBlockBoxes.end() - 1);
		aerialBlockBoxes.pop_back();
	}
	auto rightBlockBox = std::find(rightBlockBoxes.begin(), rightBlockBoxes.end(), _box);
	if (rightBlockBox != rightBlockBoxes.end())
	{
		std::iter_swap(rightBlockBox, rightBlockBoxes.end() - 1);
		rightBlockBoxes.pop_back();
	}
	auto leftBlockBox = std::find(leftBlockBoxes.begin(), leftBlockBoxes.end(), _box);
	if (leftBlockBox != leftBlockBoxes.end())
	{
		std::iter_swap(leftBlockBox, leftBlockBoxes.end() - 1);
		leftBlockBoxes.pop_back();
	}
	auto rightOneBlockBox = std::find(rightOneBlockBoxes.begin(), rightOneBlockBoxes.end(), _box);
	if (rightOneBlockBox != rightOneBlockBoxes.end())
	{
		std::iter_swap(rightOneBlockBox, rightOneBlockBoxes.end() - 1);
		rightOneBlockBoxes.pop_back();
	}
	auto rightOneBlock_02Box = std::find(rightOneBlock_02Boxes.begin(), rightOneBlock_02Boxes.end(), _box);
	if (rightOneBlock_02Box != rightOneBlock_02Boxes.end())
	{
		std::iter_swap(rightOneBlock_02Box, rightOneBlock_02Boxes.end() - 1);
		rightOneBlock_02Boxes.pop_back();
	}
	auto leftOneBlockBox = std::find(leftOneBlockBoxes.begin(), leftOneBlockBoxes.end(), _box);
	if (leftOneBlockBox != leftOneBlockBoxes.end())
	{
		std::iter_swap(leftOneBlockBox, leftOneBlockBoxes.end() - 1);
		leftOneBlockBoxes.pop_back();
	}
	auto leftOneBlock_02Box = std::find(leftOneBlock_02Boxes.begin(), leftOneBlock_02Boxes.end(), _box);
	if (leftOneBlock_02Box != leftOneBlock_02Boxes.end())
	{
		std::iter_swap(leftOneBlock_02Box, leftOneBlock_02Boxes.end() - 1);
		leftOneBlock_02Boxes.pop_back();
	}
	auto downBlockBox = std::find(downBlockBoxes.begin(), downBlockBoxes.end(), _box);
	if (downBlockBox != downBlockBoxes.end())
	{
		std::iter_swap(downBlockBox, downBlockBoxes.end() - 1);
		downBlockBoxes.pop_back();
	}
	auto goalBlockBox = std::find(goalBlockBoxes.begin(), goalBlockBoxes.end(), _box);
	if (goalBlockBox != goalBlockBoxes.end())
	{
		std::iter_swap(goalBlockBox, goalBlockBoxes.end() - 1);
		goalBlockBoxes.pop_back();
	}
	auto respawn01Box = std::find(respawn01Boxes.begin(), respawn01Boxes.end(), _box);
	if (respawn01Box != respawn01Boxes.end())
	{
		std::iter_swap(respawn01Box, respawn01Boxes.end() - 1);
		respawn01Boxes.pop_back();
	}
	auto respawn02Box = std::find(respawn02Boxes.begin(), respawn02Boxes.end(), _box);
	if (respawn02Box != respawn02Boxes.end())
	{
		std::iter_swap(respawn02Box, respawn02Boxes.end() - 1);
		respawn02Boxes.pop_back();
	}
	auto respawn03Box = std::find(respawn03Boxes.begin(), respawn03Boxes.end(), _box);
	if (respawn03Box != respawn03Boxes.end())
	{
		std::iter_swap(respawn03Box, respawn03Boxes.end() - 1);
		respawn03Boxes.pop_back();
	}
    collisionFunction.erase(_box);
}

void PhysicsWorld::AddSphere(SphereCollider * _sphere, onCollisionFunc _func)
{
	playerSpheres.emplace_back(_sphere);
    //コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
    collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_sphere), _func));
}

void PhysicsWorld::RemoveSphere(SphereCollider * _sphere)
{
	auto iter = std::find(playerSpheres.begin(), playerSpheres.end(), _sphere);
	if (iter != playerSpheres.end())
	{
		std::iter_swap(iter, playerSpheres.end() - 1);
		playerSpheres.pop_back();
	}
    collisionFunction.erase(_sphere);
}

void PhysicsWorld::SphereAndSphere()
{
	for (size_t i = 0; i < spheres.size(); i++)
	{
		if (spheres[i]->GetOwner()->GetState() != Active)
		{
			continue;
		}
		for (size_t j = i + 1; j < spheres.size(); j++)
		{
			if (spheres[j]->GetOwner()->GetState() != Active)
			{
				continue;
			}
			bool hit = Intersect(spheres[i]->GetWorldSphere(), spheres[j]->GetWorldSphere());

			if (hit)
			{
				SphereCollider* sphereA = spheres[i];
				SphereCollider* sphereB = spheres[j];

				//sphereA->GetOwner()->OnCollision(*(sphereB->GetOwner()));
				//sphereB->GetOwner()->OnCollision(*(sphereA->GetOwner()));
			}
		}
	}
}

void PhysicsWorld::BoxAndBox()
{
	for (size_t i = 0; i < boxes.size(); i++)
	{
		if (boxes[i]->GetOwner()->GetState() != Active)
		{
			continue;
		}
		for (size_t j = i + 1; j < boxes.size(); j++)
		{
			if (boxes[j]->GetOwner()->GetState() != Active)
			{
				continue;
			}
			bool hit = Intersect(boxes[i]->GetWorldBox(), boxes[j]->GetWorldBox());

			if (hit)
			{
				BoxCollider* boxA = boxes[i];
				BoxCollider* boxB = boxes[j];

				//boxA->GetOwner()->OnCollision(*(boxB->GetOwner()));
				//boxB->GetOwner()->OnCollision(*(boxA->GetOwner()));
			}
		}
	}
}

void PhysicsWorld::SphereAndBox()
{
	for (size_t i = 0; i < spheres.size(); i++)
	{
		if (spheres[i]->GetOwner()->GetState() != Active)
		{
			continue;
		}
		for (size_t j = 0; j < boxes.size(); j++)
		{
			if (boxes[j]->GetOwner()->GetState() != Active)
			{
				continue;
			}
			bool hit = Intersect(spheres[i]->GetWorldSphere(), boxes[j]->GetWorldBox());

			if (hit)
			{
				//spheres[i]->GetOwner()->OnCollision(*(boxes[j]->GetOwner()));
				//boxes[j]->GetOwner()->OnCollision(*(spheres[i]->GetOwner()));
			}
		}
	}
}

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
{
	_calcFixVec = Vector3(0, 0, 0);
	float dx1 = _fixedBox.min.x - _movableBox.max.x;
	float dx2 = _fixedBox.max.x - _movableBox.min.x;
	float dy1 = _fixedBox.min.y - _movableBox.max.y;
	float dy2 = _fixedBox.max.y - _movableBox.min.y;
	float dz1 = _fixedBox.min.z - _movableBox.max.z;
	float dz2 = _fixedBox.max.z - _movableBox.min.z;

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
