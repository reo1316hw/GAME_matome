/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos ゴール円の枠の座標
@param	_Size ゴール円の枠のサイズ
@param	_ObjectTag ゴール円の枠のタグ
@param	_SceneTag シーンのタグ
*/
GoalCircleFrame::GoalCircleFrame(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_SceneTag, _ObjectTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;

	//生成したGoalBlockの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	//回転処理
	float radian = Math::ToRadians(270);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::sUNIT_X, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}