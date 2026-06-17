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
/// 未使用のJoy-Conを取得する関数
/// </summary>
/// <param name="isLeft">true：左Joy-Con, false：右Joy-Con</param>
/// <returns>-1：エラー, それ以外：JoyConの識別ID</returns>
int ConnectJoyCon(bool isLeft)
{
	if (JoyConManager::GetInstance().CompleteInitialize() == false) return -1;

	// Joy-Conが取得できたかどうかを返す
	return JoyConManager::GetInstance().AcquireJoyCon(isLeft);
}

/// <summary>
/// 使用中のJoy-Conを未使用にする
/// </summary>
/// <param name="id">識別ID</param>
/// <returns>true：成功, false：失敗</returns>
bool DisConnectJoyCon(const int id)
{
	return JoyConManager::GetInstance().ReleaseJoyCon(id);
}

/// <summary>
/// 下ボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonDpadDown(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_DOWN);
}

/// <summary>
/// 上ボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonDpadUp(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_UP);
}

/// <summary>
/// 右ボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonDpadRight(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_RIGHT);
}

/// <summary>
/// 左ボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonDpadLeft(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_LEFT);
}

/// <summary>
/// Yボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonY(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_Y);
}

/// <summary>
/// Xボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonX(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_X);
}

/// <summary>
/// Bボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonB(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_B);
}

/// <summary>
/// Aボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonA(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_A);
}

/// <summary>
/// SRボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonSR(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_SR);
}

/// <summary>
/// SLボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonSL(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_SL);
}

/// <summary>
/// Rボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonR(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_R);
}

/// <summary>
/// Lボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonL(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_L);
}

/// <summary>
/// ZRボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonZR(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_ZR);
}

/// <summary>
/// ZLボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonZL(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_ZL);
}

/// <summary>
/// マイナスボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonMinus(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_MINUS);
}

/// <summary>
/// プラスボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonPlus(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_PLUS);
}

/// <summary>
/// スティックが押しこまれたか返す関数
/// </summary>
/// <returns>押しこまれたどうか(true：押された, false：押されていない)</returns>
bool IsButtonStick(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_STICK);
}

/// <summary>
/// キャプチャボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonCapture(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_CAPTURE);
}

/// <summary>
/// ホームボタンが押されたか返す関数
/// </summary>
/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
bool IsButtonHome(int id)
{
	auto& instance = JoyConManager::GetInstance();

	if (!instance.IsValid(id)) return false;

	return instance.IsButtonPressed(id, BUTTON_HOME);
}
