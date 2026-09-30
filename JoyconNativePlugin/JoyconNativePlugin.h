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

extern "C" JOYCONNATIVEPLUGIN_API bool JoyConInitialize();		// Joy-Conプラグインを使用可能にする関数
extern "C" JOYCONNATIVEPLUGIN_API void JoyConFinalize();		// Joy-Conプラグインの使用を終了する関数