#include "JoyConDevice.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="hdl">デバイスハンドル</param>
/// <param name="isL">左Joy-Conかどうか</param>
JoyConDevice::JoyConDevice(DeviceID id, ControllerType t) :
	ID(id),
	type(t),
	fullData()
{ }

/// <summary>
/// データを更新する(フル)
/// </summary>
/// <param name="data">生データ</param>
void JoyConDevice::UpdateData(const JoyConRawFullInputData data)
{
	fullData = data;

	// TODO:生データを加工する
}

/// <summary>
/// デバイスIDを返す
/// </summary>
/// <returns>デバイスID</returns>
DeviceID JoyConDevice::GetID() const
{
	return ID;
}