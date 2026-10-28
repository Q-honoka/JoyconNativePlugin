#include "JoyConDevice.h"
#include "JoyConUtility.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="hdl">デバイスハンドル</param>
/// <param name="isL">左Joy-Conかどうか</param>
JoyConDevice::JoyConDevice(DeviceID id, ControllerType t) :
	ID(id),
	type(t),
	processedData()
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