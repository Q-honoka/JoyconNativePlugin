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
extern "C" JOYCONNATIVEPLUGIN_API void Initialize();

// 更新処理
extern "C" JOYCONNATIVEPLUGIN_API void JoyConUpdate();

// 終了処理
extern "C" JOYCONNATIVEPLUGIN_API void Finalize();

// 下ボタンが押されたか返す関数
extern "C" JOYCONNATIVEPLUGIN_API bool IsButtonDpadDown();