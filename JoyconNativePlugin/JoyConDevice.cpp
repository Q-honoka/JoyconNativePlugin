#include "JoyConDevice.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="hdl">デバイスハンドル</param>
/// <param name="isL">左Joy-Conかどうか</param>
JoyConDevice::JoyConDevice(hid_device* hdl, bool isL) :
	mtx(),
	rawInput({0}),
	handle(hdl),
	isLeft(isL),
	isActive(false)
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
	bool updated = false;

	if (!handle)
	{
		return updated;
	}

	unsigned char buffer[64] = { 0 };  // 取得するデータのバッファサイズは64バイト

	int result = hid_read(handle, buffer, sizeof(buffer));

	// データサイズが0より大きいなら、データの処理を行う
	if (0 < result)
	{
		if (result == 64 && buffer[0] == 0x30)
		{
			// データの書き込み中は他が触れないようにする
			std::lock_guard<std::mutex> lock(mtx);
			// 最新データの格納
			JoyConRawInput temp;
			memcpy(temp.data, buffer, 64);
			rawInput = temp;

			updated = true;
		}
	}

	return updated;
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
/// Joy-Conが使用中かどうかを返す
/// </summary>
/// <returns>true：使用中, false：未使用</returns>
bool JoyConDevice::IsActive() const
{
	std::lock_guard<std::mutex> lock(mtx);

	return isActive;
}

/// <summary>
/// Joy-Conの使用フラグを変更する
/// </summary>
/// <param name="state"></param>
void JoyConDevice::SetActive(const bool state)
{
	std::lock_guard<std::mutex> lock(mtx);

	isActive = state;
}

/// <summary>
/// Joy-Conの最新の生データを返す
/// </summary>
/// <returns>Joy-Conの生データ構造体</returns>
const JoyConRawInput JoyConDevice::GetJoyConRawInput() const
{
	std::lock_guard<std::mutex> lock(mtx);

	return rawInput;
}

