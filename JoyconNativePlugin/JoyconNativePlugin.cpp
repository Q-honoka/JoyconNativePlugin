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

// 初期化処理
void Initialize()
{
	JoyConManager::GetInstance().Initialize();
}

// 更新処理
void JoyConUpdate()
{
	JoyConManager::GetInstance().Update();
}

// 終了処理
void Finalize()
{
	JoyConManager::GetInstance().Finalize();
}

// 下ボタンが押されたか返す関数
bool IsButtonDpadDown()
{
	return JoyConManager::GetInstance().IsButtonDpadDown();
}