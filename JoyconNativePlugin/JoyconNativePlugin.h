#pragma once

#ifdef JOYCONNATIVEPLUGIN_EXPORTS
#define JOYCONNATIVEPLUGIN_API __declspec(dllexport)
#else
#define JOYCONNATIVEPLUGIN_API __declspec(dllimport)
#endif // JOYCONNATIVEPLUGIN_EXPORTS


// 引数で与えられた２つの数を足した値を返す（テスト用）
extern "C" JOYCONNATIVEPLUGIN_API int Add(
	const int a, const int b);


/*
*	Joy-Conの接続・切断に関する処理関数
*/

extern "C" JOYCONNATIVEPLUGIN_API void JoyConInitialize();			// すべてのJoy-Conを取得する関数

extern "C" JOYCONNATIVEPLUGIN_API int ConnectJoyCon(bool isLeft);	// 使っていないJoy-Conを取得する関数
extern "C" JOYCONNATIVEPLUGIN_API bool DisConnectJoyCon(const int id);	// 使用中のJoy-Conを未使用にする関数

/*
*	ボタンが押されたかの取得関数。18種類。
*	Joy-Con（左）のボタン配置は縦持ちが基準。
*	押されている場合は true を返す
*	押されていない場合もしくは、適切なコントローラーでない場合は false を返す
*/

extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonDpadDown(int id);	// 下
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonDpadUp(int id);		// 上
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonDpadRight(int id);	// 右
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonDpadLeft(int id);	// 左
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonY(int id);			// Y
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonX(int id);			// X
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonB(int id);			// B
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonA(int id);			// A
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonSR(int id);			// SR
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonSL(int id);			// SL
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonR(int id);			// R
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonL(int id);			// L
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonZR(int id);			// ZR
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonZL(int id);			// ZL
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonMinus(int id);		// マイナス
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonPlus(int id);		// プラス
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonStick(int id);		// スティック押し込み
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonCapture(int id);		// キャプチャ
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonHome(int id);		// ホーム

/*
*	Joy-Conのアナログスティックデータを取得する関数
*/