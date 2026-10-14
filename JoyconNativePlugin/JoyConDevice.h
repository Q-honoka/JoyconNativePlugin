#pragma once
#include "JoyConTypes.h"

/*
	役割
	1台のJoy-Conの最新データを持つ

	責務
	・Joy-Con1台分の最新のデータを保持する

	情報
	・デバイスID
	・コントローラータイプ
	・入力レポートの種類
	・最新の入力レポート
*/

class JoyConDevice
{
public:
	JoyConDevice(DeviceID id, ControllerType t);	// コンストラクタ
	void UpdateData(const JoyConRawDefaultInputData data);		// 入力データの更新(デフォルト)
	void UpdateData(const JoyConRawFullInputData data);			// 入力データの更新(フル)
	DeviceID GetID() const;		// ID取得
	DeviceInputMode GetInputMode() const;	// 入力モードの取得

private:
	DeviceID ID;			// デバイスID
	ControllerType type;		// コントローラーの種類
	DeviceInputMode mode;		// 入力レポートのモード

	JoyConRawDefaultInputData defaultData;		// デフォルト入力生データ
	JoyConRawFullInputData fullData;			// フル入力生データ
};