#include "JoyConManager.h"
#include "hidapi.h"
#include <stdio.h>

constexpr int VENDOR_NINTENDO = 0x057E;		// 任天堂のベンダーID（1406）

constexpr int PRODUCT_JOYCON_L = 0x2006;	// Joy-Con(L)のプロダクトID（8198）
constexpr int PRODUCT_JOYCON_R = 0x2007;	// Joy-Con(R)のプロダクトID（8199）

/// <summary>
/// コンストラクタ
/// </summary>
JoyConManager::JoyConManager() :
	joycons(),
	updateThread(),
	isRunning(false)
{
}

/// <summary>
/// Joy-Conの列挙と、JoyConDeviceの生成を行う
/// </summary>
void JoyConManager::Initialize()
{
	// すべてのHIDデバイスを取得
	hid_device_info* devInfo = hid_enumerate(0, 0);
	hid_device_info* device = devInfo;

	while (device)
	{
		// Joy-Conのみ調べて、左右を判断する
		if (device->vendor_id == VENDOR_NINTENDO)
		{
			bool isLeft = device->product_id == PRODUCT_JOYCON_L;
			
			hid_device* dev = hid_open(
				device->vendor_id, 
				device->product_id, 
				device->serial_number
			);

			// 空でなければ、JoyConDeviceを生成して追加する
			if (dev != nullptr)
			{
				joycons.emplace_back(JoyConDevice(dev, isLeft));
			}
		}

		device = device->next;
	}

	hid_free_enumeration(devInfo);

	// スレッドを起動する
	isRunning = true;
	updateThread = std::thread(&JoyConManager::Update, this);
}

/// <summary>
/// すべてのJoy-Conを切断する
/// </summary>
void JoyConManager::Finalize()
{
	/*
		やること：Joy-Conの切断
		・配列の各要素の切断処理を呼ぶ
		・配列を空にする
	*/

	// スレッドの停止
	isRunning = false;
	if (updateThread.joinable())
	{
		updateThread.join();
	}
}

/// <summary>
/// すべてのJoy-Conの入力データを更新する
/// </summary>
void JoyConManager::Update()
{
	while (isRunning)
	{
		for (JoyConDevice& j : joycons)
		{
			j.Update();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}