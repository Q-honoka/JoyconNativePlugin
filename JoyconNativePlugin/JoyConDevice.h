#pragma once
#include "hidapi.h"

/*
	役割
	1台のJoy-Conと通信し、生の入力状態を最新に保つ

	責務
	・HIDAPIを使用してデバイスと通信する
	・Joy-Con1台分の最新の生データを保持する
	・接続/切断の管理

	情報
	・接続ハンドル
	・右か左か
	・接続状態
	・最新の入力レポート
*/

// Joy-Conから取得した生データ
struct JoyConRawInput
{
	// ボタンデータ
	// スティックデータ
	// 加速度データ
	// ジャイロデータ
};

class JoyConDevice
{
public:
	JoyConDevice(hid_device* hdl, bool isL);	// コンストラクタ
	bool Connect();			// 接続
	bool Disconnect();		// 切断
	bool Update();			// 入力データの更新

	bool IsConnected() const;	// 接続状態を返す
	bool IsLeft() const;		// 左コントローラーかどうかを返す

	const JoyConRawInput& GetJoyConRawInput() const;	// Joy-Conの生データを返す

private:
	JoyConRawInput rawInput;	// Joy-Conから取得した生データ
	hid_device* handle;			// デバイスハンドル
	bool isConnected = false;	// 接続状態（true：接続, false：未接続）
	bool isLeft = false;		// 左右フラグ（true：左, false：右）
};