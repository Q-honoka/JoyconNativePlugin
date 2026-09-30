#pragma once
#include "JoyConTypes.h"
#include <atomic>

#ifdef JOYCONNATIVEPLUGIN_EXPORTS
#define JOYCONNATIVEPLUGIN_API __declspec(dllexport)
#else
#define JOYCONNATIVEPLUGIN_API __declspec(dllimport)
#endif // JOYCONNATIVEPLUGIN_EXPORTS


// 引数で与えられた２つの数を足した値を返す（テスト用）
extern "C" JOYCONNATIVEPLUGIN_API int Add(
	const int a, const int b);


/*
*	プラグインの接続・切断に関する処理関数
*/

extern "C" JOYCONNATIVEPLUGIN_API bool JoyConInitialize();		// Joy-Conプラグインを使用可能にする関数
extern "C" JOYCONNATIVEPLUGIN_API void JoyConFinalize();		// Joy-Conプラグインの使用を終了する関数

/*
*	Joy-Conの接続・切断に関する処理関数
*/

extern "C" JOYCONNATIVEPLUGIN_API uint32_t JoyConConnected();	// Joy-Conと接続し、取得する関数
extern "C" JOYCONNATIVEPLUGIN_API void JoyConDisConnect(uint32_t id);		// Joy-Conと接続を解除する関数

/*
*	Joy-Conのデータ取得に関する処理関数
*/

extern "C" JOYCONNATIVEPLUGIN_API void JoyConGetRawData(uint32_t id, JoyConRawDefaultInputData* data);		// Joy-Conのデータを取得する関数（デフォルトデータ）
extern "C" JOYCONNATIVEPLUGIN_API void JoyConGetRawDataFull(uint32_t id, JoyConRawFullInputData* data);		// Joy-Conのデータを取得する関数（フルモードデータ）