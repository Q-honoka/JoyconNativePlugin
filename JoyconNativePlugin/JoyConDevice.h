#pragma once
#include "hidapi.h"
#include "JoyConTypes.h"
#include <mutex>

/*
	役割
	1台のJoy-Conと通信し、生の入力状態を最新に保つ

	責務
	・Joy-Con1台分の最新の生データを保持する
	・切断処理

	情報
	・最新の入力レポート
	・接続ハンドル
	・右か左か
*/

class JoyConDevice
{
public:
	JoyConDevice(hid_device* hdl, ControllerType t);	// コンストラクタ
	~JoyConDevice();			// デストラクタ
	bool Update();				// 入力データの更新

private:
	bool UpdateInputReport();	// 生データを更新する
	JoyConRawDefaultInputData ParseDefaultData(const unsigned char* buffer);	// デフォルトデータに入れなおす
	JoyConRawFullInputData ParseFullData(const unsigned char* buffer);	// フルデータに入れなおす
	mutable std::mutex mtx;		// 競合回避のためのミューテックス
	hid_device* handle;			// デバイスハンドル
	ControllerType type;		// コントローラーの種類
	DeviceInputMode mode;		// 入力レポートのモード

	JoyConRawDefaultInputData defaultData;		// デフォルト入力生データ
	JoyConRawFullInputData fullData;			// フル入力生データ
};