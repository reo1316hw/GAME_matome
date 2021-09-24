/*
@brief インクルード
*/
#include "pch.h"

#include "CheckpointEffectManager.h"
#include "SandEffectManager.h"
#include "ClearEffectManager.h"
#include "DeathEffectManager.h"

/*
@fn		コンストラクタ
@param	_Pos プレイヤーの座標
@param	_Size プレイヤーのサイズ
@param	_ObjectTag プレイヤーのタグ
@param	_SceneTag シーンのタグ
*/
Player::Player(const Vector3& _Pos, const Vector3& _Size, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_SceneTag, _ObjectTag)
	, mPlayerSphere(Vector3::sZERO,0.0f)
	, mVisibleFrameCount(0)
	, mLife(0)
	, mCheckpointEffectCount(0)
	, mAngle(0.0f)
	, MPlayerSpeedUp(10.0f)
	, MGroundYPos(120.0f)
	, mScene(SceneBase::Scene::eOtherScene)
	, mDeathFlag(false)
	, mDamageFlag(false)
	, mStopFlag(false)
	, mClearFlag(false)
	, mJumpFlag(false)
	, mScaleFlag(false)
	, mGroundFlag(false)
	, mCollisionFlag(true)
	, mEnableCheckpointFlag(false)
	, mRespawnFlag(false)
{
	//GameObjectメンバ変数の初期化
	mTag = _ObjectTag;
	SetScale(_Size);
	SetPosition(_Pos);
	mInitPos = _Pos;
	mRespawnPos = _Pos;

	mScene = _SceneTag;

	// 速度の値
	mMoveSpeed = 20.0f;
	mGravity   = 2.0f;
	mLife	   = 3;

	//生成したPlayerの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);

	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_GpmeshName));

	//エフェクト
	mSandEffectManager = new SandEffectManager(this, _ObjectTag, _SceneTag);
	mCheckpointEffectManager = new CheckpointEffectManager(_ObjectTag, _SceneTag, this);
	mClearEffectManager = new ClearEffectManager(_ObjectTag, _SceneTag, this);
	mDeathEffectManager = new DeathEffectManager(_ObjectTag, _SceneTag , this);

	//プレイヤー自身の当たり判定
	mSelfSphereCollider = new SphereCollider(this, GetOnCollisionFunc());
	Sphere sphere = {Vector3::sZERO, 30.0f};
	mSelfSphereCollider->SetObjectSphere(sphere);

	mLateralMoveVelocity = Vector3::sZERO;
	mButtonFlag = false;

	mMainCamera->SetPlayerPtr(this);
}

/*
@fn		プレイヤーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void Player::UpdateGameObject(float _deltaTime)
{
	//カメラの座標
	const Vector3 CameraPos = Vector3(0, 500, -550);
	//ダメージを受けるy座標
	const float DamageYPos = -700.0f;
	//ゴールz座標
	float goalZPos = 0.0f;

	//プレイヤーの斜め後ろにカメラをセット
	mMainCamera->SetViewMatrixLerpObject(CameraPos, mPosition);

	//ステージクリアしたらプレイヤーの更新を止める
	if (mClearFlag)
	{
		SetState(State::eDead);
	}

	//プレイヤーがある一定の座標まで落ちたらダメージを受ける
	if (mPosition.y <= DamageYPos)
	{
		mPosition.y = DamageYPos + 1.0f;
		mDamageFlag = true;
	}

	//ダメージを受けたら体力を減らす
	if (mDamageFlag)
	{
		mLife -= 1;
		mRespawnFlag = true;
		mDamageFlag = false;
	}

	//全ステージ共通のリスポーン処理
	if (mRespawnFlag)
	{
		mLateralMoveVelocity = Vector3::sZERO;
		mCollisionFlag = true;

		if (mLife >= 1)
		{
			mPosition = mRespawnPos;
			mStopFlag = true;
		}
	}

	//チュートリアル
	if (mScene == SceneBase::Scene::eTutorial)
	{
		//チュートリアル時の前方移動速度
		mMoveSpeed = 13.0f;
		//チュートリアル時のジャンプ力
		if (mJumpFlag)
		{
			mLateralMoveVelocity = Vector3::sZERO;
			mVelocity.y = 48.0f;
			mScaleFlag = true;
			mJumpFlag = false;
		}

		goalZPos = -75700.0f;

		//チュートリアル時のゴールの座標
		if (mPosition.z >= goalZPos)
		{
			mClearFlag = true;
		}
	}

	//ステージ01
	if (mScene == SceneBase::Scene::eStage01)
	{
		//ステージ01のジャンプ力
		if (mJumpFlag)
		{
			mLateralMoveVelocity = Vector3::sZERO;
			mVelocity.y = 40.0f;
			mScaleFlag = true;
			mJumpFlag = false;
		}

		goalZPos = -8900.0f;

		//ステージ01のゴール座標
		if (mPosition.z >= goalZPos)
		{
			mClearFlag = true;
		}
	}

	//ステージ02
	if (mScene == SceneBase::Scene::eStage02)
	{
		//ステージ02のジャンプ力
		if (mJumpFlag)
		{
			mLateralMoveVelocity = Vector3::sZERO;
			mVelocity.y = 40.0f;
			mScaleFlag = true;
			mJumpFlag = false;
		}

		goalZPos = -2100.0f;

		//ステージ02のゴールの座標
		if (mPosition.z >= goalZPos)
		{
			mClearFlag = true;
		}
	}

	//リスポーン後の待機時間中処理
	if (mStopFlag)
	{
		//表示するタイミング
		const int VisibleTiming = 10;

		mAngle = 0.0f;
		mVisibleFrameCount++;

		switch (mVisibleFrameCount % VisibleTiming)
		{
		case VisibleType::eInvisible:
			mMeshComponent->SetVisible(false);
			break;
		case VisibleType::eVisible:
			mMeshComponent->SetVisible(true);
			break;
		}

		//表示させるフレーム
		const int VisibleFlame = 40;

		mVelocity = Vector3::sZERO;
		if (mVisibleFrameCount >= VisibleFlame)
		{
			mVisibleFrameCount = 0;
			mVelocity.z = mMoveSpeed;
			mVelocity.y = mMoveSpeed;
			mStopFlag = false;

			mMeshComponent->SetVisible(true);
		}
	}
	
	//体力0になった時の処理
	if (mLife <= 0)
	{
		mDeathFlag = true;
		SetState(State::eDead);
	}

	///////////////////////////////////////////////////////
	//スケール縮小処理
	if (mScaleFlag)
	{

		mScale.y = 1.2f + (mPosition.y - MGroundYPos) * 0.0015f;
		mScale.z = 1.2f + (mPosition.y - MGroundYPos) * 0.0015f;
	}

	if (mPosition.y <= MGroundYPos && mVelocity.y <= 0.0f)
	{
		mScaleFlag = false;
		mScale.x = 1.2f;
		mScale.y = 1.2f;
		mScale.z = 1.2f;
	}
	///////////////////////////////////////////////////////

	//回転するy座標
	const float RotateYPos = 200.0f;

	//ジャンプしたときに回転を遅くする処理
	if (mPosition.y >= RotateYPos)
	{
		if (mStopFlag == false)
		{
			mAngle = 2.0f;
		}
	}
	else
	{
		mAngle = 10.0f;
	}

	//回転処理
	float radian = Math::ToRadians(mAngle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::sUNIT_X, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
	
	//最大速度
	const float PlayerMaxSpeed = 25.0f;

	//右移動の最大速度
	if (mVelocity.x >= PlayerMaxSpeed)
	{
		mVelocity.x = PlayerMaxSpeed;
	}
	//左移動の最大速度
	if (mVelocity.x <= -PlayerMaxSpeed)
	{
		mVelocity.x = -PlayerMaxSpeed;
	}

	//// 常に前に進む
	//if (!mStopFlag)
	//{
	//	mVelocity.z = mMoveSpeed;
	//}

	//ボタンを押していないときの減速処理
	if (!mButtonFlag)
	{
		//減速度
		const float PlayerSpeedDown = 4.0f;

		//速度が0より大きかった場合に右に減速
		if (mVelocity.x > 0.0f)
		{
			mVelocity.x += -PlayerSpeedDown;
		}
		//速度が0より小さかった場合に左に減速
		else if (mVelocity.x < 0.0f)
		{
			mVelocity.x += PlayerSpeedDown;
		}
		
		//速度が減速度の値と一緒になったら速度を0に固定する
		if (mVelocity.x <= PlayerSpeedDown && mVelocity.x > 0.0f ||
			mVelocity.x >= -PlayerSpeedDown && mVelocity.x < 0.0f)
		{
			mVelocity.x = 0.0f;
		}

	}

	////接地していないかつリスポーン時の待機時間じゃない時に重力処理を行う
	//if (!mGroundFlag && !mStopFlag)
	//{
	//	mVelocity.y -= mGravity;
	//}

	//当たり判定を無効にするy座標
	const float OffCollisionYPos = 50.0f;

	//プレイヤーがある一定の座標まで落ちたら当たり判定を無効にする
	if (mPosition.y < OffCollisionYPos)
	{
		mCollisionFlag = false;
	}

	//チェックポイントエフェクトを制御
	CheckpointEffectControl();

	// 常に座標に速度を足す
 	mPosition += mVelocity + mLateralMoveVelocity;

	// 他のクラスで使用するためにリスポーンフラグを保存しておく
	mSaveRespawnFlag = mRespawnFlag;

	mRespawnFlag = false;
	mGroundFlag = false;

	// 座標をセット
	SetPosition(mPosition);
}

/*
@fn	チェックポイントエフェクトを制御
*/
void Player::CheckpointEffectControl()
{
	//チェックポイントボードに当たったらエフェクトを発生するためのカウントを始める
	if (mHitCheckpointFlag)
	{
		//リセットするタイミング
		const int ResetNum = 60;

		mCheckpointEffectCount++;

		//エフェクトのフラグやカウントを数フレーム後にリセットする
		if (mCheckpointEffectCount >= ResetNum)
		{
			mHitCheckpointFlag = false;
			mCheckpointEffectCount = 0;
		}

		//カウントを始めて最初の1フレーム時に1回だけエフェクトを発生させる
		if (mCheckpointEffectCount == 1)
		{
			mEnableCheckpointFlag = true;
		}
		else
		{
			mEnableCheckpointFlag = false;
		}
	}
}

/*
@fn		入力を引数で受け取る更新関数
@brief	基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
@param	_KeyState 各入力機器の入力状態
@brief	キーボード、マウス、コントローラー
*/
void Player::GameObjectInput(const InputState& _KeyState)
{
	//コントローラー入力処理
	InputController(_KeyState);
	//アナログスティック入力処理
	InputStick(_KeyState);
}

/*
@fn コントローラー入力処理
@param	_KeyState 各入力機器の入力状態
*/
void Player::InputController(const InputState& _KeyState)
{
	// コントローラーの十字上もしくはキーボード、Wが入力されたらzを足す
	if (_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 1 ||
		_KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
	{
		mVelocity.z = mMoveSpeed;
	}
	// コントローラーの十字下もしくは、キーボードSが入力されたら-zを足す
	else if (_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1 ||
			 _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
	{
		mVelocity.z = -mMoveSpeed;
	}
	// コントローラーの十字上かコントローラーの十字下かキーボードWかキーボードSが入力されなかったら速度を0にする
	else if (_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 0  ||
			 _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 0||
			 _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) == 0 ||
			 _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) == 0)
	{
		mVelocity.z *= 0;
	}

	//コントローラーの十字左もしくは、キーボードAが入力されたら-xを足す
	if (_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 ||
		_KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
	{
		mVelocity.x += -MPlayerSpeedUp;
	}
	// コントローラーの十字右もしくは、キーボードDが入力されたらxを足す
	else if (_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 ||
		     _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
	{
		mVelocity.x += MPlayerSpeedUp;
	}

	// コントローラーの十字左かコントローラーの十字右かキーボードAかキーボードDが入力されなかったらmButtonFlagをfalseにする
	else if (_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 0 ||
		     _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 0 ||
		     _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) == 0 ||
		     _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) == 0)
	{
		mButtonFlag = false;
	}

}

/*
@fn アナログスティック入力処理
@param	_KeyState 各入力機器の入力状態
*/
void Player::InputStick(const InputState& _KeyState)
{
	//左スティックの入力値の値(-1~1)
	Vector2 leftAxis = _KeyState.m_controller.GetLAxisVec();
	//移動するための左スティックのしきい値
	const float LeftAxisThreshold = 0.3f;

	//左スティック入力時の左移動
	if (leftAxis.x <= -LeftAxisThreshold)
	{
		mVelocity.x += -MPlayerSpeedUp;
	}
	//左スティック入力時の右移動
	if (leftAxis.x >= LeftAxisThreshold)
	{
		mVelocity.x += MPlayerSpeedUp;
	}
}

/*
@fn		プレイヤーがヒットした時の処理
@param	_HitObject ヒットした対象のゲームオブジェクトのアドレス
*/
void Player::OnCollision(const GameObject& _HitObject)
{
	if (mCollisionFlag)
	{
		//ヒットしたオブジェクトのタグを取得
		mTag = _HitObject.GetTag();

		//ダメージ判定
		if (mTag == Tag::eBlockTag ||
			mTag == Tag::eVerticalBlockTag ||
			mTag == Tag::eRightBlockTag ||
			mTag == Tag::eLeftBlockTag ||
			mTag == Tag::eRightOneMoveBlockTag ||
			mTag == Tag::eLeftOneMoveBlockTag ||
			mTag == Tag::eAerialBlockTag ||
			mTag == Tag::eLowUpBlockTag)
		{
			mDamageFlag = true;
		}

		//接地判定
		if (mTag == Tag::eGroundTag ||
			mTag == Tag::eGlassTag ||
			mTag == Tag::eVerticalMoveGroundTag ||
			mTag == Tag::eRightGroundTag ||
			mTag == Tag::eLeftGroundTag ||
			mTag == Tag::eLateralMoveGroundTag ||
			mTag == Tag::eJumpTag ||
			mTag == Tag::eDownBlockTag)
		{
			//重力を消す
			mVelocity.y = 0;
			mGroundFlag = true;
		}

		//ジャンプ判定
		if (mTag == Tag::eJumpTag)
		{
			mJumpFlag = true;
		}

		//横移動床の判定
		if (mTag == Tag::eLateralMoveGroundTag)
		{
			//重力を消す
			mVelocity.y = 0;
			//横移動床の速度を取得
			mLateralMoveVelocity = mLateral->GetVelocity();
		}
		else
		{
			mLateralMoveVelocity = Vector3::sZERO;
		}

		//チェックポイントに当たった時の処理
		HitCheckPoint(_HitObject);
	}
}

/*
@fn	    チェックポイントに当たった時の処理
@param	_HitObject ヒットした対象のゲームオブジェクトのアドレス
*/
void Player::HitCheckPoint(const GameObject& _HitObject)
{
	//チェックポイント通過判定
	if (mTag == Tag::eCheckpointTag)
	{
		//リスポーン地点を少し前にずらすための定数
		const Vector3 ShiftZPos = Vector3(0.0f, 0.0f, 100.0f);
		mGroundFlag = false;
		mHitCheckpointFlag = true;
		mRespawnPos = _HitObject.GetPosition() + ShiftZPos;

		if (mPosition.y <= MGroundYPos)
		{
			mGroundFlag = true;
		}
	}
}