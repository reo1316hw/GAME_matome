/*
@brief	インクルード
*/
#include "Respawn.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"

/*
@fn		コンストラクタ
@param	_pos リスポーン地点の座標
@param	_size リスポーン地点のサイズ
@param	_objectTag リスポーン地点のタグ
@param	_sceneTag シーンのタグ
*/
Respawn::Respawn(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	// 当たり判定
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh("Assets/box.gpmesh");

	if (mTag == respawn01)
	{
		//生成したRespawn01の生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		mBoxcollider = new BoxCollider(this, ColliderTag::respawn01, GetOnCollisionFunc());
	}
	if (mTag == respawn02)
	{
		//生成したRespawn02の生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		mBoxcollider = new BoxCollider(this, ColliderTag::respawn02, GetOnCollisionFunc());
	}
	if (mTag == respawn03)
	{
		//生成したRespawn03の生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		mBoxcollider = new BoxCollider(this, ColliderTag::respawn03, GetOnCollisionFunc());
	}

	mBoxcollider->SetObjectBox(mMesh->GetBox());
}