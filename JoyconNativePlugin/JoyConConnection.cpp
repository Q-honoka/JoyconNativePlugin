#include "JoyConConnection.h"

constexpr int VENDOR_NINTENDO = 0x057E;		// 任天堂のベンダーID
constexpr int PRODUCT_JOYCON_L = 0x2006;	// Joy-Con(L)のプロダクトID
constexpr int PRODUCT_JOYCON_R = 0x2007;	// Joy-Con(R)のプロダクトID

constexpr int DEFAULT_BUF_SIZE = 0x40;		// 標準データサイズ

constexpr int SUBCOMMAND_DATA_FULLREPORT = 0x30;	// フルレポートモードのサブコマンドデータ

/// <summary>
/// コンストラクタ
/// </summary>
JoyConConnection::JoyConConnection() :
	nextDeviceID(0),
	successInit(false),
	devices()
{
	// HIDAPIの初期化
	successInit = hid_init() == 0;
}

/// <summary>
/// デストラクタ
/// </summary>
JoyConConnection::~JoyConConnection()
{
	// HIDAPIを終了する
	hid_exit();
}

/// <summary>
/// コントローラーと接続する
/// </summary>
/// <returns>デバイス情報</returns>
DeviceInfo JoyConConnection::ConnectionController()
{
	// コントローラーの種類の指定なしで接続する
	return ConnectionControllerImpl(std::nullopt);
}

/// <summary>
/// 指定したコントローラーと接続する
/// </summary>
/// <param name="type">コントローラーの種類</param>
/// <returns>デバイス情報</returns>
DeviceInfo JoyConConnection::ConnectionController(ControllerType type)
{
	// コントローラーの種類を指定して接続する
	return ConnectionControllerImpl(type);
}

/// <summary>
/// コントローラーとの接続を切断する
/// </summary>
/// <param name="id">切断したいコントローラーのデバイスID</param>
void JoyConConnection::DisconnectionController(DeviceID id)
{
	hid_close(devices[id].handle);
}

/// <summary>
/// フルレポートモードのサブコマンドを送信する
/// </summary>
/// <param name="id">フルモードにするデバイスのデバイスID</param>
/// <returns>成功したかどうか</returns>
bool JoyConConnection::SetFullReportMode(DeviceID id)
{
	// 送信するデータ
	uint8_t buf[DEFAULT_BUF_SIZE] = { 0 };

	buf[0] = 0x01;
	buf[1] = devices[id].packetNumber;
	buf[10] = 0x03;		// 入力レポート
	buf[11] = SUBCOMMAND_DATA_FULLREPORT;		// フルレポートモード

	// サブコマンドを送信できたかどうかを返す
	if (hid_write(devices[id].handle, buf, DEFAULT_BUF_SIZE) >= 0)
	{
		// パケット番号を更新する
		devices[id].packetNumber = (devices[id].packetNumber + 1) & 0x0F;
		return true;
	}

	return false;
}

/// <summary>
/// コントローラーの最新データを取得する（デフォルトモード+Joy-Con）
/// </summary>
/// <param name="id">取得したいデバイスのID</param>
/// <param name="inputData">取得したデータの格納先の参照</param>
/// <returns>取得できたか</returns>
bool JoyConConnection::GetRawInputData(DeviceID id, JoyConRawDefaultInputData& inputData)
{
	uint8_t buf[DEFAULT_BUF_SIZE] = { 0 };

	// 受け取ったデータサイズが0より大きいなら処理を続ける
	if (hid_read(devices[id].handle, buf, DEFAULT_BUF_SIZE) > 0)
	{
		// データが正しく受け取ることができていない場合は、falseを返す
		if (buf[0] != 0x3F) return false;

		// 生データを分けて格納する
		inputData.inputReportID = buf[0];
		inputData.buttonState[0] = buf[1];
		inputData.buttonState[1] = buf[2];
		inputData.stickHat = buf[3];

		return true;
	}

	return false;
}

/// <summary>
/// コントローラーの最新データを取得する（フルモード）
/// </summary>
/// <param name="id">取得したいデバイスのID</param>
/// <param name="inputData">取得したデータの格納先の参照</param>
/// <returns>取得できたか</returns>
bool JoyConConnection::GetRawInputData(DeviceID id, JoyConRawFullInputData& inputData)
{
	uint8_t buf[DEFAULT_BUF_SIZE] = { 0 };

	// 受け取ったデータサイズが0より大きいなら処理を続ける
	if (hid_read(devices[id].handle, buf, DEFAULT_BUF_SIZE) > 0)
	{
		// データが正しく受け取ることができていない場合は、falseを返す
		if (buf[0] != 0x30 && buf[0] != 0x21) return false;
		
		// 生データを分けて格納する
		inputData.inputReportID = buf[0];
		inputData.timer = buf[1];
		
		inputData.battery = (buf[2] & 0xF0);
		inputData.connection = (buf[2] & 0x0F);
		
		inputData.rightButton = buf[3];
		inputData.sharedButton = buf[4];
		inputData.leftButton = buf[5];

		inputData.leftStickHorizontal = buf[6] | ((buf[7] & 0xF0) << 8);
		inputData.leftStickVertical = (buf[7] >> 4) | (buf[8] << 4);

		inputData.rightStickHorizontal = buf[9] | ((buf[10] & 0xF0) << 8);
		inputData.rightStickVertical = (buf[10] >> 4) | (buf[11] << 4);

		inputData.rumble = buf[12];

		inputData.accelX = buf[13] | (buf[14] << 8);
		inputData.accelY = buf[15] | (buf[16] << 8);
		inputData.accelZ = buf[17] | (buf[18] << 8);

		inputData.gyro1 = buf[19] | (buf[20] << 8);
		inputData.gyro2 = buf[21] | (buf[22] << 8);
		inputData.gyro3 = buf[23] | (buf[24] << 8);

		inputData.prevAccelX = buf[25] | (buf[26] << 8);
		inputData.prevAccelY = buf[27] | (buf[28] << 8);
		inputData.prevAccelZ = buf[29] | (buf[30] << 8);

		inputData.prevGyro1 = buf[31] | (buf[32] << 8);
		inputData.prevGyro2 = buf[33] | (buf[34] << 8);
		inputData.prevGyro3 = buf[35] | (buf[36] << 8);

		inputData.priorAccelX = buf[37] | (buf[38] << 8);
		inputData.priorAccelY = buf[39] | (buf[40] << 8);
		inputData.priorAccelZ = buf[41] | (buf[42] << 8);

		inputData.priorGyro1 = buf[43] | (buf[44] << 8);
		inputData.priorGyro2 = buf[45] | (buf[46] << 8);
		inputData.priorGyro3 = buf[47] | (buf[48] << 8);

		return true;
	}

	return false;
}

/// <summary>
/// スティックの校正値を取得する
/// </summary>
/// <param name="id">取得したいデバイスのID</param>
/// <param name="calibrationData">校正値の格納先の参照</param>
/// <returns>取得できたか</returns>
bool JoyConConnection::GetRawStickCalibrationData(DeviceID id, RawStickCalibrationData& calibrationData)
{
	// 送信するデータ
	uint8_t buf[DEFAULT_BUF_SIZE] = { 0 };

	// 左スティック
	buf[0] = 0x01;
	buf[1] = devices[id].packetNumber;
	buf[10] = 0x10;		// SPI読み取り
	// 読み取り開始位置アドレス x603D
	buf[11] = 0x3D;
	buf[12] = 0x60;
	buf[13] = 0x00;
	buf[14] = 0x00;
	// 読み取るサイズ
	buf[15] = 18;

	// 送信結果が0未満なら、取得失敗
	if (hid_write(devices[id].handle, buf, DEFAULT_BUF_SIZE) < 0) 
		return false;

	// 読み取ったデータが0より大きいなら処理を続ける
	if (hid_read(devices[id].handle, buf, DEFAULT_BUF_SIZE) > 0)
	{
		// 応答がなければ取得失敗
		if (buf[0] != 0x21) return false;

		// 左スティックの校正値
		calibrationData.leftStickValue[0] = (buf[20] << 8) & 0xF00 | buf[19];
		calibrationData.leftStickValue[1] = (buf[21] << 4) | (buf[20] >> 4);
		calibrationData.leftStickValue[2] = (buf[23] << 8) & 0xF00 | buf[22];
		calibrationData.leftStickValue[3] = (buf[24] << 4) | (buf[23] >> 4);
		calibrationData.leftStickValue[4] = (buf[26] << 8) & 0xF00 | buf[25];
		calibrationData.leftStickValue[5] = (buf[27] << 4) | (buf[26] >> 4);

		// 右スティックの校正値
		calibrationData.rightStickValue[0] = (buf[29] << 8) & 0xF00 | buf[28];
		calibrationData.rightStickValue[1] = (buf[30] << 4) | (buf[29] >> 4);
		calibrationData.rightStickValue[2] = (buf[32] << 8) & 0xF00 | buf[31];
		calibrationData.rightStickValue[3] = (buf[33] << 4) | (buf[32] >> 4);
		calibrationData.rightStickValue[4] = (buf[35] << 8) & 0xF00 | buf[34];
		calibrationData.rightStickValue[5] = (buf[36] << 4) | (buf[35] >> 4);

		return true;
	}

	return false;
}

/// <summary>
/// デバイスID生成して返す
/// </summary>
/// <returns>デバイスID</returns>
DeviceID JoyConConnection::CreateDeviceID()
{
	// 加算前の値が返される
	return nextDeviceID.fetch_add(1);
}

/// <summary>
/// 種類に応じたプロダクトIDを取得する
/// </summary>
/// <param name="type">コントローラーの種類</param>
/// <returns>プロダクトID</returns>
int JoyConConnection::GetProductID(ControllerType type)
{
	switch (type)
	{
	case ControllerType::JOYCON_LEFT:
		return PRODUCT_JOYCON_L;
	case ControllerType::JOYCON_RIGHT:
		return PRODUCT_JOYCON_R;
	default:
		return -1;
	}
}

/// <summary>
/// プロダクトIDからコントローラーの種類を取得する
/// </summary>
/// <param name="productID">プロダクトID</param>
/// <returns>コントローラーの種類</returns>
ControllerType JoyConConnection::GetControllerType(int productID)
{
	switch (productID)
	{
	case PRODUCT_JOYCON_L:
		return ControllerType::JOYCON_LEFT;
	case PRODUCT_JOYCON_R:
		return ControllerType::JOYCON_RIGHT;
	default:
		return ControllerType::JOYCON_LEFT;
	}
}

/// <summary>
/// コントローラーと接続する内部関数
/// </summary>
/// <param name="type">コントローラーのタイプの有無</param>
/// <returns>デバイス情報</returns>
DeviceInfo JoyConConnection::ConnectionControllerImpl(std::optional<ControllerType> requestType)
{
	// 接続されているすべてのHIDデバイスを取得
	hid_device_info* devInfo = hid_enumerate(0, 0);
	hid_device_info* device = devInfo;

	// デバイスハンドル
	hid_device* handle = nullptr;

	while (device)
	{
		// Joy-Conのみ調べる
		if (device->vendor_id == VENDOR_NINTENDO)
		{
			// タイプが指定されている場合は、プロダクトIDを調べる
			if (requestType)
			{
				// プロダクトIDが一致しなければ、次のデバイスを調べる
				if (device->product_id != GetProductID(*requestType))
				{
					device = device->next;
					continue;
				}
			}

			// すでに開いたことのあるデバイスなら、次のデバイスを調べる
			if (devicePaths.contains(device->path))
			{
				device = device->next;
				continue;
			}

			// デバイスを開く
			handle = hid_open_path(device->path);

			// ハンドルが存在しない場合は、次のデバイスを調べる
			if (!handle)
			{
				device = device->next;
				continue;
			}

			// ハンドルとパスの登録
			DeviceID id = CreateDeviceID();
			ControllerInfo info = 
			{ 
				handle, 
				device->path, 
				0 
			};
			devices.emplace(id, info);
			devicePaths.insert(std::string(device->path));
			// デバイス情報を作成して返す
			return
			{
				id,
				GetControllerType(device->product_id),
				true
			};
		}

		device = device->next;
	}

	// 見つからなかったら接続失敗を返す
	return
	{
		0,
		ControllerType::JOYCON_LEFT,
		false
	};
}