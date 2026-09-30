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

/// <summary>
/// Joy-Conの接続処理
/// </summary>
/// <returns>Joy-ConのデバイスID</returns>
uint32_t JoyConConnected()
{
	return JoyConManager::GetInstance().Connected();
}

/// <summary>
/// Joy-Conの接続解除処理
/// </summary>
/// <param name="id">接続を解除したいJoy-ConのデバイスID</param>
void JoyConDisConnect(uint32_t id)
{
	return JoyConManager::GetInstance().DisConnect(id);
}

/// <summary>
/// Joy-Conのデータ取得処理（デフォルト）
/// </summary>
/// <param name="data">取得したデータの格納先</param>
void JoyConGetRawData(uint32_t id, JoyConRawDefaultInputData* data)
{
	*data = JoyConManager::GetInstance().GetRawData(id);
}

/// <summary>
/// Joy-Conのデータ取得処理（フルモード）
/// </summary>
/// <param name="data">取得したデータの格納先</param>
void JoyConGetRawDataFull(uint32_t id, JoyConRawFullInputData* data)
{
	*data = JoyConManager::GetInstance().GetRawDataFull(id);
}