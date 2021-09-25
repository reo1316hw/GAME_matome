/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Pos ゴールワ－プホールの座標
@param	_Size ゴールワ－プホールのサイズ
@param	_ObjectTag ゴールワ－プホールのタグ
@param	_SceneTag シーンのタグ
@param  _playerPtr プレイヤーのポインタ
*/
GoalWarpHole::GoalWarpHole(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, Player* _playerPtr)
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

	//自身のポインタをプレイヤークラスに設定
	_playerPtr->SetGoalWarpHolePtr(this);
}