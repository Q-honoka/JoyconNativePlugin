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