#include "JoyConDevice.h"
#include "JoyConConnection.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="hdl">デバイスハンドル</param>
/// <param name="isL">左Joy-Conかどうか</param>
JoyConDevice::JoyConDevice(DeviceID id, ControllerType t) :
	ID(id),
	type(t),
	mode(DeviceInputMode::MODE_DEFAULT),
	defaultData(),
	fullData()
{
}

/// <summary>
/// デストラクタで接続を切断する
/// </summary>
JoyConDevice::~JoyConDevice()
{
	
}

/// <summary>
/// 入力データを更新する
/// </summary>
/// <returns>true：成功, false：失敗</returns>
bool JoyConDevice::Update()
{
	// 生データを更新する
	return UpdateInputReport();
}

/// <summary>
/// 生データを更新する
/// </summary>
/// <returns>更新できたら true を返す</returns>
bool JoyConDevice::UpdateInputReport()
{
	bool updated = false;		// 更新できたか

	return updated;
}