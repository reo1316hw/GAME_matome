/*
@brief	インクルード
*/
#include "pch.h"
/*
@fn		コンストラクタ
@param	_pos 空中ブロックの座標
@param	_size 空中ブロックのサイズ
@param	_objectTag 空中ブロックのタグ
@param	_sceneTag シーンのタグ
*/
AerialBlock::AerialBlock(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//生成したAerialBlockの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/box_15.gpmesh"));

	//当たり判定
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh("Assets/box_15.gpmesh");
	mBoxcollider = new BoxCollider(this, ColliderTag::aerialBlockTag, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());
}