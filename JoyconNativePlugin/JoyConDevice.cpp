#include "JoyConDevice.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="hdl">デバイスハンドル</param>
/// <param name="isL">左Joy-Conかどうか</param>
JoyConDevice::JoyConDevice(hid_device* hdl, ControllerType t) :
	mtx(),
	handle(hdl),
	type(t),
	mode(DeviceInputMode::MODE_DEFAULT)
{
}

/// <summary>
/// デストラクタで接続を切断する
/// </summary>
JoyConDevice::~JoyConDevice()
{
	if (handle)
	{
		hid_close(handle);
		handle = nullptr;
	}
}

/// <summary>
/// 入力データを更新する
/// </summary>
/// <returns>true：成功, false：失敗</returns>
bool JoyConDevice::Update()
{
	if (!handle)
	{
		return false;
	}

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

	unsigned char buffer[64] = { 0 };
	int result = hid_read(handle, buffer, sizeof(buffer));

	// データを取得できたら、更新する
	if (0 < result)
	{
		// 現在の入力レポートのモードに応じて、取得するデータ量を変える
		switch (mode)
		{
		case DeviceInputMode::MODE_DEFAULT:	// デフォルトモード
			if (buffer[0] == 0x3F)
			{
				defaultData = ParseDefaultData(buffer);
				updated = true;
			}
			break;
		case DeviceInputMode::MODE_FULL:	// フルモード
			if (buffer[0] == 0x30)
			{
				fullData = ParseFullData(buffer);
				updated = true;
			}
			break;
		default:
			break;
		}
	}

	return updated;
}

/// <summary>
/// 渡された生データを中身を変えずにデフォルトレポート用の構造体に入れなおす
/// </summary>
/// <param name="buffer">生データ</param>
/// <returns>入れなおしたデータ</returns>
JoyConRawDefaultInputData JoyConDevice::ParseDefaultData(const unsigned char* buffer)
{
	JoyConRawDefaultInputData data = { 0 };

	// データを編集中に読み取られないよう、ロックをかける
	std::lock_guard<std::mutex> lock(mtx);

	data.inputReportID = buffer[0];
	std::copy(buffer + 1, buffer + 2, data.buttonState);
	data.stickHat = buffer[3];

	return data;
}

/// <summary>
/// 渡された生データを中身を変えずにフルレポート用の構造体に入れなおす
/// </summary>
/// <param name="buffer">生データ</param>
/// <returns>入れなおした生データ</returns>
JoyConRawFullInputData JoyConDevice::ParseFullData(const unsigned char* buffer)
{
	JoyConRawFullInputData data = { 0 };

	// データを編集中に読み取られないよう、ロックをかける
	std::lock_guard<std::mutex> lock(mtx);

	data.inputReportID = buffer[0];
	data.timer = buffer[1];
	data.battery = buffer[2] & 0xF0;
	data.connection = buffer[2] & 0x0F;

	data.rightButton = buffer[3];
	data.sharedButton = buffer[4];
	data.leftButton = buffer[5];

	data.leftStickHorizontal = buffer[6] | ((buffer[7] & 0xF) << 8);
	data.leftStickVertical = (buffer[7] >> 4) | (buffer[8] << 4);
	data.rightStickHorizontal = buffer[9] | ((buffer[10] & 0xF) << 8);
	data.rightStickVertical = (buffer[10] >> 4) | (buffer[11] << 4);

	data.rumble = buffer[12];

	std::copy(buffer + 13, buffer + 14, data.accelX);
	std::copy(buffer + 15, buffer + 16, data.accelY);
	std::copy(buffer + 17, buffer + 18, data.accelZ);
	std::copy(buffer + 19, buffer + 20, data.gyro1);
	std::copy(buffer + 21, buffer + 22, data.gyro2);
	std::copy(buffer + 23, buffer + 24, data.gyro3);
	std::copy(buffer + 25, buffer + 26, data.prevAccelX);
	std::copy(buffer + 27, buffer + 28, data.prevAccelY);
	std::copy(buffer + 29, buffer + 30, data.prevAccelZ);
	std::copy(buffer + 31, buffer + 32, data.prevGyro1);
	std::copy(buffer + 33, buffer + 34, data.prevGyro2);
	std::copy(buffer + 35, buffer + 36, data.prevGyro3);
	std::copy(buffer + 37, buffer + 38, data.priorAccelX);
	std::copy(buffer + 39, buffer + 40, data.priorAccelY);
	std::copy(buffer + 41, buffer + 42, data.priorAccelZ);
	std::copy(buffer + 43, buffer + 44, data.priorGyro1);
	std::copy(buffer + 45, buffer + 46, data.priorGyro2);
	std::copy(buffer + 47, buffer + 48, data.priorGyro3);

	return data;
}