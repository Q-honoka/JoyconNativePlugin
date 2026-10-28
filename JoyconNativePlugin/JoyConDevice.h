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
	・最新の入力レポート
*/

class JoyConDevice
{
public:
	JoyConDevice(DeviceID id, ControllerType t);	// コンストラクタ
	void UpdateData(const JoyConRawFullInputData data);			// 入力データの更新(フル)
	void SetCalibrationData(StickCalibrationData data);	// 校正値の設定
	DeviceID GetID() const;		// ID取得
	BatteryState GetBatteryState() const;	// バッテリーの状態を返す
	bool GetButtonState(ButtonType type) const;	// ボタンの状態を返す
	bool IsGetCalibrationData() const;	// 校正値を取得したか返す

private:
	JoyConProcessedFullData ProcessedJoyConFullData(const JoyConRawFullInputData& data);

	DeviceID ID;			// デバイスID
	ControllerType type;		// コントローラーの種類
	bool getCalibrationData;	// 校正値を取得したかどうか

	JoyConProcessedFullData processedData;		// 加工済みフル入力データ
	StickCalibrationData stickCalibrationData;	// スティックの校正値
};