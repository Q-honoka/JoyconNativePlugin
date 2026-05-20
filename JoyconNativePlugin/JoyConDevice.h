#pragma once
#include "hidapi.h"

/*
	役割
	1台のJoy-Conと通信し、生の入力状態を最新に保つ

	責務
	・Joy-Con1台分の最新の生データを保持する

	情報
	・接続ハンドル
	・右か左か
	・最新の入力レポート
*/

// Joy-Conから取得した生データ
struct JoyConRawInput
{	
	unsigned char data[64];
	/* 
	[0]		データの種類
	[1]		フレームカウンタ
	[2]		バッテリーと接続状態
	[3～5]	ボタンデータ
	[6～11]	システムデータ（開発では使用しない）
	[12]	振動応答
	[13～18]スティックデータ
	[19～48]モーションセンサー
	*/
};

class JoyConDevice
{
public:
	JoyConDevice(hid_device* hdl, bool isL);	// コンストラクタ
	~JoyConDevice();			// デストラクタ
	bool Update();				// 入力データの更新
	bool IsLeft() const;		// 左コントローラーかどうかを返す

	const JoyConRawInput& GetJoyConRawInput() const;	// Joy-Conの生データを返す

private:
	JoyConRawInput rawInput;	// Joy-Conから取得した生データ
	hid_device* handle;			// デバイスハンドル
	bool isLeft = false;		// 左右フラグ（true：左, false：右）
};