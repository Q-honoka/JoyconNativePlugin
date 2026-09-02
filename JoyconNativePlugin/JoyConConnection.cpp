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
/// JoyConと接続する
/// </summary>
/// <returns>デバイス情報</returns>
DeviceInfo JoyConConnection::ConnectionJoyCon()
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
	bool isConnect = true;

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

			// ハンドルがない場合は、接続失敗
			if (!handle)
			{
				isConnect = false;
			}

			// Joy-Conの左右を設定する
			switch (device->product_id)
			{
			case PRODUCT_JOYCON_L:
				info.type = ControllerType::JOYCON_LEFT;
				break;
			case PRODUCT_JOYCON_R:
				info.type = ControllerType::JOYCON_RIGHT;
				break;
			default:
				// 存在しないタイプの場合は接続失敗とする
				isConnect = false;
				break;
			}
		}
	}

	// ハンドルがない場合は、接続失敗
	if (!handle)
	{
		isConnect = false;
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