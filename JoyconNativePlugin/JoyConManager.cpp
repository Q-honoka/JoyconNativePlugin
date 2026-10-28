#include "JoyConManager.h"

constexpr uint32_t ERROR_VALUE = 0xFFFFFFFF;

/// <summary>
/// コンストラクタ
/// </summary>
JoyConManager::JoyConManager() :
	joycons(),
	joyconConnection(),
	updateThread(),
	isRunning(false)
{
}

/// <summary>
/// インスタンスの参照を返す
/// </summary>
/// <returns></returns>
JoyConManager& JoyConManager::GetInstance()
{
	static JoyConManager instance;
	return instance;
}

/// <summary>
/// プラグインの開始処理を行う
/// </summary>
bool JoyConManager::Initialize()
{
	bool result = joyconConnection.SuccessInit();
	// HIDAPIの初期化に失敗したらfalseを返す
	if (!result)
		return false;

	// スレッドを起動する
	isRunning = true;
	updateThread = std::thread(&JoyConManager::Update, this);

	return true;
}

/// <summary>
/// プラグインの終了処理を行う
/// </summary>
void JoyConManager::Finalize()
{
	// スレッドの停止
	isRunning = false;

	if (updateThread.joinable())
	{
		updateThread.join();
	}

	// 配列を空にする（デストラクタで接続解除している）
	joycons.clear();
}

/// <summary>
/// Joy-Conとの接続を開始する
/// </summary>
/// <returns>Joy-ConのデバイスID</returns>
DeviceID JoyConManager::Connected()
{
	// 1台のJoy-Conと接続して、情報を取得
	DeviceInfo info = joyconConnection.ConnectionController();

	// 取得に成功したら、デバイスタイプに応じた登録をする
	if (info.isConnected)
	{
		joycons.emplace_back(std::make_unique<JoyConDevice>(info.deviceID, info.type));
		return info.deviceID;
	}

	return ERROR_VALUE;
}

/// <summary>
/// Joy-Conとの接続を解除する
/// </summary>
/// <param name="id">切断を解除したいJoy-ConのデバイスID</param>
void JoyConManager::DisConnect(DeviceID id)
{
	auto it = std::find_if(joycons.begin(), joycons.end(),
		[id](const std::unique_ptr<JoyConDevice>& device)
		{
			return device->GetID() == id;
		});
	if (it != joycons.end()) joycons.erase(it);
	joyconConnection.DisconnectionController(id);
}

/// <summary>
/// すべてのJoy-Conの入力データを更新する
/// </summary>
void JoyConManager::Update()
{
	while (isRunning)
	{
		for (auto& j : joycons)
		{
			if (!isRunning) break;

			// 校正値を取得していなければ、取得する
			if (j->IsGetCalibrationData() == false)
			{
				printf("校正値を取得\n");
				StickCalibrationData data;
				if (joyconConnection.GetStickCalibrationData(j->GetID(), data))
				{
					j->SetCalibrationData(data);
					printf("校正値を取得完了\n");
				}
			}

			JoyConRawFullInputData data;
			if (joyconConnection.GetRawInputData(j->GetID(), data))
			{
				j->UpdateData(data);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

/// <summary>
/// バッテリーの状態を返す
/// </summary>
/// <param name="id">状態を取得するデバイスID</param>
/// <returns>バッテリーの状態を表す列挙子</returns>
BatteryState JoyConManager::GetBatteryState(DeviceID id) const
{
	auto it = std::find_if(joycons.begin(), joycons.end(),
		[id](const std::unique_ptr<JoyConDevice>& device)
		{
			return device->GetID() == id;
		});

	// 指定のIDがある場合、状態を返す
	if (it != joycons.end())
	{
		return (*it)->GetBatteryState();
	}

	// ない場合は、エラーを返す
	return BatteryState::BATTERY_ERROR;
}

/// <summary>
/// ボタンの状態を返す
/// </summary>
/// <param name="id">デバイスID</param>
/// <param name="type">ボタンの種類</param>
/// <returns>押されている場合は true を返す</returns>
bool JoyConManager::GetButtonState(DeviceID id, ButtonType type) const
{
	auto it = std::find_if(joycons.begin(), joycons.end(),
		[id](const std::unique_ptr<JoyConDevice>& device)
		{
			return device->GetID() == id;
		});

	// 指定のIDがある場合、状態を返す
	if (it != joycons.end())
	{
		return (*it)->GetButtonState(type);
	}

	// ない場合は、false を返す
	return false;
}