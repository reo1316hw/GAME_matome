/*
@brief	インクルード
*/
#include <cstring>
#include <stdio.h>
#include <limits.h>
#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>

#include "pch.h"

//コントローラーが接続されたかのフラグの初期化
bool InputSystem::mControllerConnected = 0;

/*
@fn		現在のキーの入力状態のみを取得する
@param	_keyCode SDL_Scancodeのキーコード
@return	true : 押されている , false : 押されていない(bool型)
*/
bool KeyboardState::GetKeyValue(SDL_Scancode _keyCode) const
{
	return mCurrState[_keyCode] == 1;
}

/*
@fn		現在と1フレーム前の状態からButtonStateを返す
@param	_keyCode SDL_Scancodeのキーコード
@return	ButtonState型の現在の状態(enum型 ButtonState)
*/
ButtonState KeyboardState::GetKeyState(SDL_Scancode _keyCode) const
{
	if (mPrevState[_keyCode] == 0)
	{
		if (mCurrState[_keyCode] == 0)
		{
			return ButtonState::eNone;
		}
		else
		{
			return ButtonState::ePressed;
		}
	}
	else // Prev state must be 1
	{
		if (mCurrState[_keyCode] == 0)
		{
			return ButtonState::eReleased;
		}
		else
		{
			return ButtonState::eHeld;
		}
	}
}

/*
@fn		現在の入力状態のみを取得する
@param	_button SDL_BUTTON定数
@return	true : 押されている , false : 押されていない(bool型)
*/
bool MouseState::GetButtonValue(int _button) const
{
	return (SDL_BUTTON(_button) & mCurrButtons) == 1;
}

/*
@fn		現在と1フレーム前の状態からButtonStateを返す
@param	_button SDL_BUTTON定数
@return	ButtonState型の現在の状態(enum型 ButtonState)
*/
ButtonState MouseState::GetButtonState(int _button) const
{
	int mask = SDL_BUTTON(_button);
	if ((mask & mPrevButtons) == 0)
	{
		if ((mask & mCurrButtons) == 0)
		{
			return ButtonState::eNone;
		}
		else
		{
			return ButtonState::ePressed;
		}
	}
	else
	{
		if ((mask & mCurrButtons) == 0)
		{
			return ButtonState::eReleased;
		}
		else
		{
			return ButtonState::eHeld;
		}
	}
}

/*
@brief	現在の入力状態のみを取得する
@param	_button SDL_GameControllerButtonのボタンコード
@return	true : 押されている , false : 押されていない(bool型)
*/
bool ControllerState::GetButtonValue(SDL_GameControllerButton _button) const
{
	return mCurrButtons[_button] == 1;
}

/*
@brief	現在と1フレーム前の状態からButtonStateを返す
@param	_button SDL_GameControllerButtonのボタンコード
@return	ButtonState型の現在の状態(enum型 ButtonState)
*/
ButtonState ControllerState::GetButtonState(SDL_GameControllerButton _button) const
{
	if (mPrevButtons[_button] == 0)
	{
		if (mCurrButtons[_button] == 0)
		{
			return ButtonState::eNone;
		}
		else
		{
			return ButtonState::ePressed;
		}
	}
	else // Prev state must be 1
	{
		if (mCurrButtons[_button] == 0)
		{
			return ButtonState::eReleased;
		}
		else
		{
			return ButtonState::eHeld;
		}
	}
}

/*
@fn		スティックの入力を0~32767で返す
@param	_IAxis どのスティックのどの値を取得するか
	    (左スティックのXを取得...SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX)
@return スティックの入力情報(float型)
*/
float ControllerState::GetAxisValue(const SDL_GameControllerAxis _IAxis) const
{
	return mAxisValues[_IAxis];
}

/*
@fn		初期化処理
@return true : 成功 , false : 失敗(bool型)
*/
bool InputSystem::Initialize()
{
	//キーボードの初期化処理
	//今のキーボードの状態を割り当てる
	mState.m_keyboard.mCurrState = SDL_GetKeyboardState(NULL);
	//１フレーム前の入力状態を初期化する
	memset(mState.m_keyboard.mPrevState, 0,
		SDL_NUM_SCANCODES);

	memset(mState.m_controller.mAxisValues, 0,
		sizeof(float) * SDL_CONTROLLER_AXIS_MAX);


	//現在と１フレーム前のマウスの入力状態を初期化する
	mState.m_mouse.mCurrButtons = 0;
	mState.m_mouse.mPrevButtons = 0;

	// パッドの設定ファイル gamecontrollerdb.txt の読み込みと問題が無いかのチェック
	int iNumOfControllers = SDL_GameControllerAddMappingsFromFile("Assets/Config/GameControllerdb.txt");
	if (iNumOfControllers == -1)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "Error loading database [%s]", SDL_GetError());
		return false;
	}

	//コントローラーを開く
	mController = nullptr;
	mController = SDL_GameControllerOpen(0);
	if (mController != nullptr)
	{
		mControllerConnected = true;
	}
	if (SDL_IsGameController(0))
	{
		printf("Controller :: %s \n", SDL_GameControllerMapping(mController));
	}

	// コントローライベントの無視（こちらからフレーム毎に状態を取得するため）
	SDL_GameControllerEventState(SDL_IGNORE);

	return true;
}

/*
@fn	終了処理
*/
void InputSystem::Shutdown()
{
	if (!mController)
	{
		SDL_GameControllerClose(mController);
	}
	mController = nullptr;
}

/*
@fn	Updateの準備をする（SDL_PollEventsの直前に呼ぶ）
*/
void InputSystem::PrepareForUpdate()
{
	//現在の入力状態を１フレーム前の入力状態にコピーする
	//キーボード
	memcpy(mState.m_keyboard.mPrevState,
		mState.m_keyboard.mCurrState,
		SDL_NUM_SCANCODES);

	//マウス
	mState.m_mouse.mPrevButtons = mState.m_mouse.mCurrButtons;
	mState.m_mouse.mRelativeFlag = false;
	mState.m_mouse.mScrollWheel = Vector2::sZERO;

	//コントローラー
	memcpy(mState.m_controller.mPrevButtons,
		mState.m_controller.mCurrButtons,
		SDL_CONTROLLER_BUTTON_MAX);
}

/*
@fn	フレーム毎の処理（SDL_PollEventsの直後に呼ぶ）
*/
void InputSystem::Update()
{
	//マウス
	int x = 0, y = 0;
	if (mState.m_mouse.mRelativeFlag)
	{
		mState.m_mouse.mCurrButtons =
			SDL_GetRelativeMouseState(&x, &y);
	}
	else
	{
		mState.m_mouse.mCurrButtons =
			SDL_GetMouseState(&x, &y);
	}

	mState.m_mouse.mMousePos.x = static_cast<float>(x) - 1024.0f / 2;
	mState.m_mouse.mMousePos.y = 768.0f / 2 - static_cast<float>(y);

	// コントローラが無い場合は early exitする
	if (mController != NULL)
	{
		// 前のフレームのコントローラの状態をコピーする
		memcpy(&mState.m_controller.mPrevButtons, &mState.m_controller.mCurrButtons, sizeof(Uint8) * SDL_CONTROLLER_BUTTON_MAX);

		// コントローラの状態を更新する
		SDL_GameControllerUpdate();

		// 現在のコントローラのボタン状態を保存
		for (int b = 0; b < SDL_CONTROLLER_BUTTON_MAX; ++b)
		{
			mState.m_controller.mCurrButtons[b] = SDL_GameControllerGetButton(mController, (SDL_GameControllerButton)b);
		}

		// 現在のコントローラの軸情報を保存
		for (int a = 0; a < SDL_CONTROLLER_AXIS_MAX; ++a)
		{
			mState.m_controller.mAxisValues[a] = SDL_GameControllerGetAxis(mController, (SDL_GameControllerAxis)a);
		}

		// LPAD入力をベクトル化する
		const float MaxInput = 32767.0f;
		mState.m_controller.mLAxis.x = (float)mState.m_controller.mAxisValues[SDL_CONTROLLER_AXIS_LEFTX];
		mState.m_controller.mLAxis.y= (float)mState.m_controller.mAxisValues[SDL_CONTROLLER_AXIS_LEFTY];
		
		//printf("%f\n", (float)state.Controller.axisValues[SDL_CONTROLLER_AXIS_LEFTX]);
		//スティックの入力に最低値を設ける(定数以下はカット)
		mState.m_controller.mLAxis.x= (fabs(mState.m_controller.mLAxis.x) < (float)7849) ? 0.0f : mState.m_controller.mLAxis.x / MaxInput;
		mState.m_controller.mLAxis.y= (fabs(mState.m_controller.mLAxis.y) < (float)8689) ? 0.0f : mState.m_controller.mLAxis.y / MaxInput;

	}
}

/*
@fn		SDLイベントをInputSystemに渡す
@param	_event SDLイベント
*/
void InputSystem::ProcessEvent(SDL_Event& _event)
{
	switch (_event.type)
	{
	case SDL_MOUSEWHEEL:
		mState.m_mouse.mScrollWheel = Vector2(
			static_cast<float>(_event.wheel.x),
			static_cast<float>(_event.wheel.y));
		break;
	default:
		break;
	}
}

/*
@fn		マウスのモードを設定する
@param	_value true : 相対モード , false : デフォルトモード
*/
void InputSystem::SetRelativeMouseMode(bool _value)
{
	SDL_bool set = _value ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);

	mState.m_mouse.mRelativeFlag = _value;
}

/*
@brief  入力された値（int）をフィルタリングする（範囲内に収めて-1.0~1.0にまとめる）
@param	_input 入力された値（int）
@return	フィルタリングされた値(float型)
*/
float InputSystem::Filter1D(int _input)
{
	//デッドゾーン（この値より小さいなら0.0にする）
	const int DeadZone = 250;
	//最大値（この値より大きくても1.0にする）
	const int MaxValue = 30000;

	float retVal = 0.0f;

	//入力値の絶対値を取る
	int absValue = _input > 0 ? _input : -_input;
	//入力値がデッドゾーンより小さいなら
	if (absValue > DeadZone)
	{
		//デッドゾーンと最大値の間で1.0以下になるよう計算する
		retVal = static_cast<float>(absValue - DeadZone) /
			(MaxValue - DeadZone);
		//符号を元の値と同じにする
		retVal = _input > 0 ? retVal : -1.0f * retVal;
		//-1.0~1.0の間に収める
		retVal = Math::Clamp(retVal, -1.0f, 1.0f);
	}

	return retVal;
}

/*
@brief  入力された値（int）をフィルタリングする（範囲内に収めて0.0~1.0にまとめる）
@param	_inputX 入力された値のx（int）
@param	_inputY 入力された値のy（int）
@return	フィルタリングされた値(Vector2型)
*/
Vector2 InputSystem::Filter2D(int _inputX, int _inputY)
{
	//デッドゾーン（この値より小さいなら0.0にする）
	const float DeadZone = 8000.0f;
	//最大値（この値より大きくても1.0にする）
	const float MaxValue = 30000.0f;

	//2次元ベクトルにする
	Vector2 dir;
	dir.x = static_cast<float>(_inputX);
	dir.y = static_cast<float>(_inputY);

	float length = dir.Length();

	//入力値のベクトルの長さがデッドゾーンより小さいなら
	if (length < DeadZone)
	{
		dir = Vector2::sZERO;
	}
	else
	{
		//デッドゾーンと最大値の間で1.0以下になるよう計算する
		float f = (length - DeadZone) / (MaxValue - DeadZone);
		//0.0と1.0の間に収める
		f = Math::Clamp(f, 0.0f, 1.0f);
		//ベクトルを正規化して、分数の値にスケーリングする
		dir *= f / length;
	}

	return dir;
}
