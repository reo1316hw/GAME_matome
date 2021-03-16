#include "AerialBlock.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"

AerialBlock::AerialBlock(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, objectTag)
{
	//GameObjectメンバ変数の初期化
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//生成したTestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	meshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/box_15.gpmesh"));

	//当たり判定
	mesh = new Mesh;
	mesh = RENDERER->GetMesh("Assets/box_15.gpmesh");
	boxcollider = new BoxCollider(this, ColliderTag::aerialBlockTag, GetOnCollisionFunc());
	boxcollider->SetObjectBox(mesh->GetBox());
}