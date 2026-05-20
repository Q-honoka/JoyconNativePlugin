#include "JoyConDevice.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="hdl">デバイスハンドル</param>
/// <param name="isL">左Joy-Conかどうか</param>
JoyConDevice::JoyConDevice(hid_device* hdl, bool isL) :
	rawInput({0}),
	handle(hdl),
	isLeft(isL)
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

	unsigned char buffer[64];  // 取得するデータのバッファサイズは64バイト

	int result = hid_read(handle, buffer, sizeof(buffer));

	// データサイズが0より大きいなら、データの処理を行う
	if (0 < result)
	{
		if (buffer[0] == 0x30)
		{
			// 最新データの格納
			memcpy(rawInput.data, buffer, 64);
			return true;
		}
		return false;
	}

	return false;

}

/// <summary>
/// Joy-Conが左かどうかを返す
/// </summary>
/// <returns>true：成功, false：失敗</returns>
bool JoyConDevice::IsLeft() const
{
	return isLeft;
}

/// <summary>
/// Joy-Conの最新の生データを返す
/// </summary>
/// <returns>Joy-Conの生データ構造体</returns>
const JoyConRawInput& JoyConDevice::GetJoyConRawInput() const
{
	return rawInput;
}