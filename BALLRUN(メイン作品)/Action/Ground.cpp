#include "Ground.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Player.h"

Ground::Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		mMeshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box.gpmesh"));

		// 当たり判定
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh("Assets/box.gpmesh");
		mBoxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		mBoxcollider->SetObjectBox(mMesh->GetBox());

		break;
	case SceneBase::Scene::stage01:

		//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		mMeshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box_08.gpmesh"));

		// 当たり判定
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh("Assets/box_08.gpmesh");
		mBoxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		mBoxcollider->SetObjectBox(mMesh->GetBox());

		break;
	case SceneBase::Scene::stage02:

		//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		mMeshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box_13.gpmesh"));

		// 当たり判定
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh("Assets/box_13.gpmesh");
		mBoxcollider = new BoxCollider(this, ColliderTag::blockTag, GetOnCollisionFunc());
		mBoxcollider->SetObjectBox(mMesh->GetBox());

		break;
	}
}
