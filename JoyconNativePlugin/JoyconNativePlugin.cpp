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
bool JoyConInitialize()
{
	return JoyConManager::GetInstance().Initialize();
}

/// <summary>
/// Joy-Conの終了処理
/// </summary>
void JoyConFinalize()
{
	JoyConManager::GetInstance().Finalize();
}