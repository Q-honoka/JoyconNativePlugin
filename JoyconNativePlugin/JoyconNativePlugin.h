#pragma once

#ifdef JOYCONNATIVEPLUGIN_EXPORTS
#define JOYCONNATIVEPLUGIN_API __declspec(dllexport)
#else
#define JOYCONNATIVEPLUGIN_API __declspec(dllimport)
#endif // JOYCONNATIVEPLUGIN_EXPORTS


// 引数で与えられた２つの数を足した値を返す（テスト用）
extern "C" JOYCONNATIVEPLUGIN_API int Add(
	const int a, const int b);

// 初期化処理
extern "C" JOYCONNATIVEPLUGIN_API void JoyConInitialize();

/*
*	Joy-Conの接続・切断に関する処理関数
*/

/*
*	ボタンが押されたかの取得関数。18種類。
*	Joy-Con（左）のボタン配置は縦持ちが基準。
*	押されている場合は true を返す
*	押されていない場合もしくは、適切なコントローラーでない場合は false を返す
*/

extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonDpadDown();		// 下
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonDpadUp();		// 上
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonDpadRight();		// 右
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonDpadLeft();		// 左
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonY();				// Y
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonX();				// X
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonB();				// B
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonA();				// A
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonSR();			// SR
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonSL();			// SL
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonR();				// R
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonL();				// L
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonZR();			// ZR
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonZL();			// ZL
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonMinus();			// マイナス
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonPlus();			// プラス
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonStick();			// スティック押し込み
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonCapture();		// キャプチャ
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonHome();			// ホーム

/*
*	Joy-Conのアナログスティックデータを取得する関数
*/