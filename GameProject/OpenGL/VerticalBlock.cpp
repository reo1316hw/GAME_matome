/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos 縦長障害物の座標
@param	_Size 縦長障害物のサイズ
@param	_ObjectTag 縦長障害物のタグ
@param	_SceneTag シーンのタグ
*/
VerticalBlock::VerticalBlock(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_SceneTag, _ObjectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;

	//生成したVerticalBlockの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	// 当たり判定
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_GpmeshName);
	mBoxcollider = new BoxCollider(this, GetOnCollisionFunc());
	mBoxcollider->SetObjectBox(mMesh->GetBox());
}