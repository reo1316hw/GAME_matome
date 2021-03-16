#include "Respawn.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"

Respawn::Respawn(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, objectTag)
{
	//GameObjectƒƒ“ƒo•Ï”‚Ì‰Šú‰»
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// “–‚½‚è”»’è
	mesh = new Mesh;
	mesh = RENDERER->GetMesh("Assets/box.gpmesh");

	if (tag == respawn01)
	{
		boxcollider = new BoxCollider(this, ColliderTag::respawn01, GetOnCollisionFunc());
	}
	if (tag == respawn02)
	{
		boxcollider = new BoxCollider(this, ColliderTag::respawn02, GetOnCollisionFunc());
	}
	if (tag == respawn03)
	{
		boxcollider = new BoxCollider(this, ColliderTag::respawn03, GetOnCollisionFunc());
	}

	boxcollider->SetObjectBox(mesh->GetBox());
}