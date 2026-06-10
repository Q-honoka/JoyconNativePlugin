#include "pch.h"
#include "JoyconNativePlugin.h"
#include "JoyConManager.h"

// 引数で与えられた２つの数を足した値を返す
int Add(
	const int a,
	const int b)
{
	return a + b;
}

/// <summary>
/// Joy-Conの初期化処理
/// </summary>
void JoyConInitialize()
{
	JoyConManager::GetInstance().Initialize();
}

/// <summary>
/// 下ボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonDpadDown()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_DOWN);
}

/// <summary>
/// 上ボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonDpadUp()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_UP);
}

/// <summary>
/// 右ボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonDpadRight()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_RIGHT);
}

/// <summary>
/// 左ボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonDpadLeft()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_LEFT);
}

/// <summary>
/// Yボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonY()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_Y);
}

/// <summary>
/// Xボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonX()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_X);
}

/// <summary>
/// Bボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonB()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_B);
}

/// <summary>
/// Aボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonA()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_A);
}

/// <summary>
/// SRボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonSR()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_SR);
}

/// <summary>
/// SLボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonSL()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_SL);
}

/// <summary>
/// Rボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonR()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_R);
}

/// <summary>
/// Lボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonL()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_L);
}

/// <summary>
/// ZRボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonZR()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_ZR);
}

/// <summary>
/// ZLボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonZL()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_ZL);
}

/// <summary>
/// マイナスボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonMinus()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_MINUS);
}

/// <summary>
/// プラスボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonPlus()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_PLUS);
}

/// <summary>
/// スティックが押しこまれたか返す関数
/// </summary>
/// <returns>押しこまれたどうか(true：押された, false：押されていない)</returns>
bool IsButtonStick()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_STICK);
}

/// <summary>
/// キャプチャボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonCapture()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_CAPTURE);
}

/// <summary>
/// ホームボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonHome()
{
	return JoyConManager::GetInstance().IsButtonPressed(0, BUTTON_HOME);
}
