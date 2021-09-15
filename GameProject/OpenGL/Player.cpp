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
@param	_pos プレイヤーの座標
@param	_size プレイヤーのサイズ
@param	_objectTag プレイヤーのタグ
@param	_sceneTag シーンのタグ
*/
Player::Player(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
	, mPlayerSphere(Vector3::Zero,0.0f)
	, mVisibleFrameCount(0)
	, mLife(0)
	, mCheckpointEffectCount(0)
	, mAngle(0.0f)
	, mScene(SceneBase::other)
	, mDeathFlag(false)
	, mDamageFlag(false)
	, mStopFlag(false)
	, mClearFlag(false)
	, mJumpFlag(false)
	, mScaleFlag(false)
	, mGroundFlag(false)
	, mCollisionFlag(true)
	, mCheckpointFlag(false)
	, mRespawnFlag(false)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);
	mInitPos = _pos;
	mRespawnPos = _pos;

	mScene = _sceneTag;

	// 速度の値
	mMoveSpeed = PLAYER_CONSTANT_SPEED;
	mGravity   = GRAVITY_ACCEL;
	mLife	  = PLAYER_LIFE;

	//生成したPlayerの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);

	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));

	//エフェクト
	mSandEffectManager = new SandEffectManager(this, _objectTag, _sceneTag);
	mCheckpointEffectManager = new CheckpointEffectManager(_objectTag, _sceneTag, this);
	mClearEffectManager = new ClearEffectManager(_objectTag, _sceneTag, this);
	mDeathEffectManager = new DeathEffectManager(_objectTag, _sceneTag , this);

	//プレイヤー自身の当たり判定
	mSelfSphereCollider = new SphereCollider(this, ColliderTag::playerTag, GetOnCollisionFunc());
	Sphere sphere = { Vector3::Zero,30.0f };
	mSelfSphereCollider->SetObjectSphere(sphere);

	mLateralMoveVelocity = Vector3::Zero;
	mButtonFlag = false;
}

/*
@fn		プレイヤーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void Player::UpdateGameObject(float _deltaTime)
{
	//プレイヤーの斜め後ろにカメラをセット
	mMainCamera->SetViewMatrixLerpObject(Vector3(0, 500, -550), mPosition);

	//ステージクリアしたらプレイヤーの更新を止める
	if (mClearFlag)
	{
		SetState(State::Dead);
	}

	//プレイヤーがある一定の座標まで落ちたらダメージを受ける
	if (mPosition.y <= -700.0f)
	{
		mPosition.y = -699.0f;
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
		mLateralMoveVelocity = Vector3::Zero;
		mCollisionFlag = true;

		if (mLife >= 1)
		{
			mPosition = mRespawnPos;
			mStopFlag = true;
		}
	}

	//チュートリアル
	if (mScene == SceneBase::tutorial)
	{
		//チュートリアル時の前方移動速度
		mMoveSpeed = TUTORIAL_MOVE_SPEED;
		//チュートリアル時のジャンプ力
		if (mJumpFlag)
		{
			mLateralMoveVelocity = Vector3::Zero;
			mVelocity.y = TUTORIAL_JUMP_SPEED;
			mScaleFlag = true;
			mJumpFlag = false;
		}

		//チュートリアル時のゴールの座標
		if (mPosition.z >= -75700)
		{
			mClearFlag = true;
		}
	}

	//ステージ01
	if (mScene == SceneBase::stage01)
	{
		//ステージ01のジャンプ力
		if (mJumpFlag)
		{
			mLateralMoveVelocity = Vector3::Zero;
			mVelocity.y = JUMP_SPEED;
			mScaleFlag = true;
			mJumpFlag = false;
		}

		//ステージ01のゴール座標
		if (mPosition.z >= -8900)
		{
			mClearFlag = true;
		}
	}

	//ステージ02
	if (mScene == SceneBase::stage02)
	{
		//ステージ02のジャンプ力
		if (mJumpFlag)
		{
			mLateralMoveVelocity = Vector3::Zero;
			mVelocity.y = JUMP_SPEED;
			mScaleFlag = true;
			mJumpFlag = false;
		}

		//ステージ02のゴールの座標
		if (mPosition.z >= -2100)
		{
			mClearFlag = true;
		}
	}

	//リスポーン後の待機時間中処理
	if (mStopFlag)
	{
		mAngle = 0.0f;

		mVisibleFrameCount++;
		if (mVisibleFrameCount % 10 == 0)
		{
			mMeshComponent->SetVisible(false);
		}

		if (mVisibleFrameCount % 10 == 5)
		{
			mMeshComponent->SetVisible(true);
		}

		mVelocity = Vector3::Zero;
		if (mVisibleFrameCount >= 40)
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
		SetState(State::Dead);
	}

	///////////////////////////////////////////////////////
	//スケール縮小処理
	if (mScaleFlag)
	{
		mScale.y = 1.2f + (mPosition.y - 120.0f) * 0.0015f;
		mScale.z = 1.2f + (mPosition.y - 120.0f) * 0.0015f;
	}
	if (mPosition.y <= 120.0f && mVelocity.y <= 0.0f)
	{
		mScaleFlag = false;
		mScale.x = 1.2f;
		mScale.y = 1.2f;
		mScale.z = 1.2f;
	}
	///////////////////////////////////////////////////////

	//ジャンプしたときに回転を遅くする処理
	if (mPosition.y >= 200)
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
	Quaternion inc(Vector3::UnitX, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
	
	//右移動の最大速度
	if (mVelocity.x >= PLAYER_MAX_SPEED)
	{
		mVelocity.x = PLAYER_MAX_SPEED;
	}
	//左移動の最大速度
	if (mVelocity.x <= -PLAYER_MAX_SPEED)
	{
		mVelocity.x = -PLAYER_MAX_SPEED;
	}

	// 常に前に進む
	if (mStopFlag == false)
	{
		mVelocity.z = mMoveSpeed;
	}

	//ボタンを押していないときの減速処理
	if (mButtonFlag == false)
	{
		//速度が0より大きかった場合に右に減速
		if (mVelocity.x > 0.0f)
		{
			mVelocity.x += -PLAYER_SPEED_DOWN;
		}
		//速度が0より小さかった場合に左に減速
		else if (mVelocity.x < 0.0f)
		{
			mVelocity.x += PLAYER_SPEED_DOWN;
		}
		
		//速度が減速度の値と一緒になったら速度を0に固定する
		if (mVelocity.x <= PLAYER_SPEED_DOWN && mVelocity.x > 0.0f ||
			mVelocity.x >= -PLAYER_SPEED_DOWN && mVelocity.x < 0.0f)
		{
			mVelocity.x = 0.0f;
		}

	}

	//接地していないかつリスポーン時の待機時間じゃない時に重力処理を行う
	if (mGroundFlag == false && mStopFlag == false)
	{
		mVelocity.y -= mGravity;
	}

	//プレイヤーがある一定の座標まで落ちたら当たり判定を無効にする
	if (mPosition.y < 30.0f)
	{
		mCollisionFlag = false;
	}

	//チェックポイントエフェクト生成器の生存時間が1になったらチェックポイントエフェクトを発生させないようにする
	if (mCheckpointEffectCount == 1)
	{
		mCheckpointFlag = false;
		mCheckpointEffectCount = 0;
	}

	//チェックポイントを通過したらチェックポイントエフェクト生成器の生存時間をカウントする
	if (mCheckpointFlag)
	{
		mCheckpointEffectCount++;
	}

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
@fn		入力を引数で受け取る更新関数
@brief	基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
@param	_keyState 各入力機器の入力状態
@brief	キーボード、マウス、コントローラー
*/
void Player::GameObjectInput(const InputState& _keyState)
{
	 //コントローラーの十字左もしくは、キーボードAが入力されたら-xを足す
	if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
	{
		mVelocity.x += -PLAYER_SPEED_UP;
	}
	// コントローラーの十字右もしくは、キーボードDが入力されたらxを足す
	else if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
	{
		mVelocity.x += PLAYER_SPEED_UP;
	}

	// コントローラーの十字左かコントローラーの十字右かキーボードAかキーボードDが入力されなかったらmButtonFlagをfalseにする
	else if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 0 ||
		_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 0 ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) == 0 ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) == 0)
	{
		mButtonFlag = false;
	}
}

/*
@fn		プレイヤーがヒットした時の処理
@param	_hitObject ヒットした対象のゲームオブジェクトのアドレス
*/
void Player::OnCollision(const GameObject& _hitObject)
{
	if (mCollisionFlag)
	{
		//ヒットしたオブジェクトのタグを取得
		mTag = _hitObject.GetTag();

		//ジャンプ判定
		if (mTag == jump)
		{
			mJumpFlag = true;
		}

		//チェックポイント通過判定
		if (mTag == checkpoint)
		{
			mCheckpointFlag = true;
			mRespawnPos = _hitObject.GetPosition();
		}

		//ダメージ判定
		if (mTag == block ||
			mTag == verticalBlock ||
			mTag == rightBlock ||
			mTag == leftBlock ||
			mTag == rightOneMoveBlock ||
			mTag == leftOneMoveBlock ||
			mTag == aerialBlock ||
			mTag == upBlock)
		{
			mDamageFlag = true;
		}

		//接地判定
		if (mTag == ground ||
			mTag == glass ||
			mTag == verticalMoveGround ||
			mTag == rightGround ||
			mTag == leftGround ||
			mTag == lateralMoveGround ||
			mTag == jump ||
			mTag == downBlock)
		{
			//重力を消す
			mVelocity.y = 0;
			mGroundFlag = true;
		}

		//横移動床の判定
		if (mTag == lateralMoveGround)
		{
			//重力を消す
			mVelocity.y = 0;
			//横移動床の速度を取得
			mLateralMoveVelocity = mLateral->GetVelocity();
		}
		else
		{
			mLateralMoveVelocity = Vector3::Zero;
		}
	}
}