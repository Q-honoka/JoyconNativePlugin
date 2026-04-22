#include "JoyConDevice.h"
#include "hidapi.h"

/// <summary>
/// Joy-Conとの通信を接続する
/// </summary>
/// <returns>true：成功, false：失敗</returns>
bool JoyConDevice::Connect()
{
	/*
		やること：接続処理
		・1台のJoy-Conと通信を開始する
		・成功したらisConnectedをtrueにして、trueを返す
		・失敗したらfalseを返す
	*/
	return false;
}

/// <summary>
/// Joy-Conとの通信を切断する
/// </summary>
/// <returns>true：成功, false：失敗</returns>
bool JoyConDevice::Disconnect()
{
	/*
		やること：切断処理
		・1台のJoy-Conと通信を切断する
		・成功したらisConnectedをfalseにして、trueを返す
		・失敗したらfalseを返す
	*/
	return false;
}

/// <summary>
/// 入力データを更新する
/// </summary>
/// <returns>true：成功, false：失敗</returns>
bool JoyConDevice::Update()
{
	/*
		やること：更新処理
		・Joy-Conから1フレーム分の生データを取得する
		・取得できなかったらfalseを返す
		・取得できたらtrueを返す
	*/
	return false;
}

/// <summary>
/// Joy-Conとの接続状態を返す
/// </summary>
/// <returns>true：成功, false：失敗</returns>
bool JoyConDevice::IsConnected() const
{
	return isConnected;
}

/// <summary>
/// Joy-Conが左かどうかを返す
/// </summary>
/// <returns>true：成功, false：失敗</returns>
bool JoyConDevice::IsLeft() const
{
	return isLeft;
}

/// <summary>
/// Joy-Conの最新の生データを返す
/// </summary>
/// <returns>Joy-Conの生データ構造体</returns>
const JoyConRawInput& JoyConDevice::GetJoyConRawInput() const
{
	return rawInput;
}