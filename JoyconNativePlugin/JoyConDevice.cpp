#include "JoyConDevice.h"
#include "JoyConUtility.h"
#include <iostream>

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="hdl">デバイスハンドル</param>
/// <param name="isL">左Joy-Conかどうか</param>
JoyConDevice::JoyConDevice(DeviceID id, ControllerType t) :
	ID(id),
	type(t),
	getCalibrationData(false),
	processedData(),
	stickCalibrationData()
{ }

/// <summary>
/// データを更新する(フル)
/// </summary>
/// <param name="data">生データ</param>
void JoyConDevice::UpdateData(const JoyConRawFullInputData data)
{
	// TODO:生データを加工する
	processedData = ProcessedJoyConFullData(data);
}

/// <summary>
/// 校正値を設定する
/// </summary>
/// <param name="data">スティックデータの校正値</param>
void JoyConDevice::SetCalibrationData(StickCalibrationData data)
{
	stickCalibrationData = data;
	getCalibrationData = true;
}

/// <summary>
/// デバイスIDを返す
/// </summary>
/// <returns>デバイスID</returns>
DeviceID JoyConDevice::GetID() const
{
	return ID;
}

/// <summary>
/// バッテリーの状態を返す
/// </summary>
/// <returns>バッテリーの状態を表す列挙子</returns>
BatteryState JoyConDevice::GetBatteryState() const
{
	return processedData.batteryState;
}

/// <summary>
/// ボタンの状態を返す
/// </summary>
/// <param name="type">ボタンの種類</param>
/// <returns>押されている場合は true を返す</returns>
bool JoyConDevice::GetButtonState(ButtonType type) const
{
	return processedData.buttonState[(int)type];
}

/// <summary>
/// 校正値を取得したかどうかを返す
/// </summary>
/// <returns>取得していたら true を返す</returns>
bool JoyConDevice::IsGetCalibrationData() const
{
	return getCalibrationData;
}

/// <summary>
/// JoyConの生データを加工する
/// </summary>
/// <param name="data">生データ</param>
/// <returns>加工後データ</returns>
JoyConProcessedFullData JoyConDevice::ProcessedJoyConFullData(const JoyConRawFullInputData& data)
{
	JoyConProcessedFullData temp = { };

	temp.batteryState = ProcessBatteryData(data.battery);	// バッテリー
	ProcessButtonData(data.buttonState, temp.buttonState);	// ボタンデータ

	return temp;
}