/*
@brief インクルード
*/
#include "pch.h"

//ゲームオブジェクトのID、カウント用の初期化
int GameObject::mGameObjectId = 0;
//メインカメラの初期化　生成はGameObjectManager生成時に行われる
MainCameraObject* GameObject::mMainCamera = nullptr;
//ゲームオブジェクトの更新を止めるイベント状態の初期化
PauzingEvent GameObject::mPauzingEvent = PauzingEvent::NoneEvent;

/*
@fn		コンストラクタ
@param	_SceneTag シーンのタグ
@param	_ObjectTag ゲームオブジェクトのタグ
@param	_reUseGameObject
*/
GameObject::GameObject(SceneBase::Scene _SceneTag,const Tag& _ObjectTag, bool _reUseGameObject)
	: mState(Active)
	, mWorldTransform()
	, mPosition(Vector3::sZERO)
	, mVelocity(Vector3::sZERO)
	, mAabb(Vector3::sZERO, Vector3::sZERO)
	, mScale(Vector3(1.0f, 1.0f, 1.0f))
	, mRotation(Quaternion::sIDENTITY)
	, mMyObjectId(mGameObjectId)
	, mTag(_ObjectTag)
	, mSceneTag(_SceneTag)
	, mMoveSpeed(0.0f)
	, mGravity(0.0f)
	, mReUseObject(_reUseGameObject)
	, mRecomputeWorldTransform(true)
	, mHitFlag(false)
{
	mGameObjectId++;
	//GameObjectManagerにポインタを渡す
	GAME_OBJECT_MANAGER->AddGameObject(this);
}

/*
@fn	デストラクタ
*/
GameObject::~GameObject()
{
	//GameObjectManagerからポインタを削除する
	GAME_OBJECT_MANAGER->RemoveGameObject(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}

}

/*
@fn		フレーム毎の処理
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void GameObject::Update(float _deltaTime)
{
	//更新停止のイベント中でないか(ポーズ画面など)
	if (mPauzingEvent == PauzingEvent::NoneEvent)
	{
		if (mState == Active)
		{
			//Transformのワールド変換
			ComputeWorldTransform();
			//ゲームオブジェクトの更新
			UpdateGameObject(_deltaTime);
			//このゲームオブジェクトに付属するコンポーネントの更新
			UpdateComponents(_deltaTime);
			//Transformのワールド変換
			ComputeWorldTransform();
		}
	}
	//ポーズ画面のときコンポーネントを更新させない(アニメーションなども止めるため)
	else if(mPauzingEvent == PauzingEvent::PausingEvent)
	{
		PausingUpdateGameObject();
	}
	else
	{
		PausingUpdateGameObject();
		UpdateComponents(_deltaTime);
	}
}

/*
@fn		アタッチされてるコンポーネントのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void GameObject::UpdateComponents(float _deltaTime)
{
	if (mState != Dead)
	{	
		for (auto itr : mComponents)
		{
			itr->Update(_deltaTime);
		}
	}
}

/*
@fn		ゲームオブジェクトのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void GameObject::UpdateGameObject(float _deltaTime)
{
}

/*
@fn		ゲームオブジェクトが静止中に更新されるアップデート関数
@brief	pauzingUpdateがtrueのときだけ呼ばれる更新関数
*/
void GameObject::PausingUpdateGameObject()
{
}

/*
@fn		入力状態を受け取りGameObjectとComponentの入力更新関数を呼び出す
@param	_KeyState 各入力機器の入力状態
@brief	キーボード、マウス、コントローラー
*/
void GameObject::ProcessInput(const InputState& _KeyState)
{
	if (mState == Active)
	{
		//コンポーネントの入力関数にコントローラーの入力状態を
		for (auto comp : mComponents)
		{
			comp->ProcessInput(_KeyState);
		}
		//ゲームオブジェクトの入力関数にコントローラーの入力状態を
		GameObjectInput(_KeyState);
	}
}

/*
@fn		入力を引数で受け取る更新関数
@brief	基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
@param	_KeyState 各入力機器の入力状態
@brief	キーボード、マウス、コントローラー
*/
void GameObject::GameObjectInput(const InputState & _KeyState)
{
}

/*
@fn		コンポーネントを追加する
@param	_component 追加するコンポーネントのポインタ
*/
void GameObject::AddComponent(Component * _component)
{
	int order = _component->GetUpdateOder();
	auto itr = mComponents.begin();
	for (;
		itr != mComponents.end();
		++itr)
	{
		if (order < (*itr)->GetUpdateOder())
		{
			break;
		}
	}
	mComponents.insert(itr, _component);
}

/*
@fn		コンポーネントを削除する
@param	_component 削除するコンポーネントのポインタ
*/
void GameObject::RemoveComponent(Component * _component)
{
	auto itr = std::find(mComponents.begin(), mComponents.end(), _component);
	if (itr != mComponents.end())
	{
		mComponents.erase(itr);
	}
}

/*
@fn			現在の仕様上行うことができない処理を外部から強引に行うための関数
@exsample	ゲームオブジェクト全体の更新が停止中に対象のゲームオブジェクトを更新する
*/
void GameObject::ExceptionUpdate()
{
	ComputeWorldTransform();

	UpdateGameObject(0.016f);
	UpdateComponents(0.016f);

	ComputeWorldTransform();
}

/*
@fn	Transformのワールド変換
*/
void GameObject::ComputeWorldTransform()
{
	//ワールド変換が必要かどうか？
	//もし必要だったらワールド変換を行う
	if (mRecomputeWorldTransform)
	{
		//objectの
		//変換が必要フラグを降ろす
		mRecomputeWorldTransform = false;
		//スケールのワールド変換
		mWorldTransform = Matrix4::CreateScale(mScale);
		//回転のワールド変換（クウォータニオン）
		mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
		//平行移動の更新
		mWorldTransform *= Matrix4::CreateTranslation(mPosition);

		//object（owner）が持っているcomponentによる座標変換系
		for (auto itr : mComponents)
		{
			itr->OnUpdateWorldTransform();
		}
	}
}

/*
@fn		矩形と矩形の押し戻し
@param	_MyAABB	基準にするオブジェクトの矩形当たり判定
@param	_PairAABB ヒットするオブジェクトの矩形当たり判定
@param	_PairTag ヒットするオブジェクトのタグ
*/
void GameObject::FixCollision(const AABB & _MyAABB, const AABB & _PairAABB, const Tag& _PairTag)
{
	Vector3 ment = Vector3(0, 0, 0);
	CalcCollisionFixVec(_MyAABB, _PairAABB, ment);
	SetPosition(GetPosition() + (ment));
}

/*
@fn		前方ベクトルの向きに回転する
@param	_forward 向かせたい前方方向ベクトル
*/
void GameObject::RotateToNewForward(const Vector3& _Forward)
{
	// X軸ベクトル(1,0,0)とforwardの間の角度を求める
	float dot = Vector3::Dot(Vector3::sUNIT_X, _Forward);
	float angle = Math::Acos(dot);
	//printf("%f\n", angle);
	// 下向きだった場合
	if (dot > 0.9999f)
	{
		SetRotation(Quaternion::sIDENTITY);
	}
	// 上向きだった場合
	else if (dot < -0.9999f)
	{
		SetRotation(Quaternion(Vector3::sUNIT_Z, Math::Pi));
	}
	else
	{
		// 軸ベクトルとforwardとの外積から回転軸をもとめ、回転させる
		Vector3 axis = Vector3::Cross(Vector3::sUNIT_X, _Forward);
		axis.Normalize();
		SetRotation(Quaternion(axis, angle));
	}
}

/*
@fn 静的なmainCameraを生成する
*/
void GameObject::CreateMainCamera()
{
	mMainCamera = new MainCameraObject();
}