#include "Respawn.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"

Respawn::Respawn(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
{
	//GameObjectƒƒ“ƒo•Ï”‚Ì‰Šú‰»
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// “–‚½‚è”»’è
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh("Assets/box.gpmesh");

	if (mTag == respawn01)
	{
		mBoxcollider = new BoxCollider(this, ColliderTag::respawn01, GetOnCollisionFunc());
	}
	if (mTag == respawn02)
	{
		mBoxcollider = new BoxCollider(this, ColliderTag::respawn02, GetOnCollisionFunc());
	}
	if (mTag == respawn03)
	{
		mBoxcollider = new BoxCollider(this, ColliderTag::respawn03, GetOnCollisionFunc());
	}

	mBoxcollider->SetObjectBox(mMesh->GetBox());
}