#include "JoyConConnection.h"

constexpr int VENDOR_NINTENDO = 0x057E;		// 任天堂のベンダーID
constexpr int PRODUCT_JOYCON_L = 0x2006;	// Joy-Con(L)のプロダクトID
constexpr int PRODUCT_JOYCON_R = 0x2007;	// Joy-Con(R)のプロダクトID

/// <summary>
/// コンストラクタ
/// </summary>
JoyConConnection::JoyConConnection() :
	nextDeviceID(0),
	successInit(false),
	devices()
{
	// hidapiの初期化
	if (hid_init() != 0)
	{
		successInit = false;
	}

	successInit = true;
}

/// <summary>
/// コントローラーと接続する
/// </summary>
/// <returns>デバイス情報</returns>
DeviceInfo JoyConConnection::ConnectionController()
{
	DeviceInfo info = {
		0,
		ControllerType::JOYCON_LEFT,
		false
	};	

	// 接続されているすべてのHIDデバイスを取得
	hid_device_info* devInfo = hid_enumerate(0, 0);
	hid_device_info* device = devInfo;

	// デバイスハンドル
	hid_device* handle = nullptr;
	bool isConnect = false;

	// すべてのデバイスを捜査する
	while (device)
	{
		// JoyConのみ調べる
		if (device->vendor_id == VENDOR_NINTENDO)
		{
			// 開いたことのあるデバイスは開かない
			if (devicePaths.contains(device->path)) continue;

			// デバイスを開く
			handle = hid_open(
				device->vendor_id,
				device->product_id,
				device->serial_number
			);

			// ハンドルがあれば接続成功
			if (handle) isConnect = true;

			// コントローラーの種類を設定する
			switch (device->product_id)
			{
			case PRODUCT_JOYCON_L:
				info.type = ControllerType::JOYCON_LEFT;
				break;
			case PRODUCT_JOYCON_R:
				info.type = ControllerType::JOYCON_RIGHT;
				break;
			default:
				// 存在しない種類なら接続失敗とする
				isConnect = false;
				break;
			}

		}
	}

	// 接続が成功していたら生成IDを作成する
	if (isConnect)
	{
		info.deviceID = CreateDeviceID();
	}
	info.isConnected = isConnect;

	return info;
}

/// <summary>
/// 指定したコントローラーと接続する
/// </summary>
/// <param name="type">コントローラーの種類</param>
/// <returns>デバイス情報</returns>
DeviceInfo JoyConConnection::ConnectionController(ControllerType type)
{
	DeviceInfo info = {
	0,
	type,
	false
	};

	// 接続されているすべてのHIDデバイスを取得
	hid_device_info* devInfo = hid_enumerate(0, 0);
	hid_device_info* device = devInfo;

	// デバイスハンドル
	hid_device* handle = nullptr;
	bool isConnect = false;
	int deviceType;

	// 指定された種類のプロダクトIDを設定
	switch (type)
	{
	case ControllerType::JOYCON_LEFT:
		deviceType = PRODUCT_JOYCON_L;
		break;
	case ControllerType::JOYCON_RIGHT:
		deviceType = PRODUCT_JOYCON_R;
		break;
	}

	// すべてのデバイスを捜査する
	while (device)
	{
		// JoyConのみ調べる
		if (device->vendor_id == VENDOR_NINTENDO)
		{
			// 開いたことのあるデバイスは開かない
			if (devicePaths.contains(device->path)) continue;

			if (device->product_id != deviceType) continue;

			// デバイスを開く
			handle = hid_open(
				device->vendor_id,
				device->product_id,
				device->serial_number
			);

			if (handle) isConnect = true;
		}
	}

	// 接続が成功していたら生成IDを作成する
	if (isConnect)
	{
		info.deviceID = CreateDeviceID();
	}
	info.isConnected = isConnect;

	return info;
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