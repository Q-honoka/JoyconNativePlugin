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
uint32_t JoyConManager::Connected()
{
	// 1台のJoy-Conと接続して、情報を取得
	DeviceInfo info = joyconConnection.ConnectionController();

	// 取得に成功したら、デバイスタイプに応じた登録をする
	if (info.isConnected)
	{
		bool isL = false;
		switch (info.type)
		{
			case ControllerType::JOYCON_LEFT:
				isL = true;
				break;
			case ControllerType::JOYCON_RIGHT:
			default:
				break;
		}

		joycons.emplace_back(info.deviceID, isL);
		return info.deviceID;
	}

	return ERROR_VALUE;
}

/// <summary>
/// Joy-Conとの接続を解除する
/// </summary>
/// <param name="id">切断を解除したいJoy-ConのデバイスID</param>
void JoyConManager::DisConnect(uint32_t id)
{
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
			if (j->IsActive() == false) continue;	// 使用中のJoy-Conのみデータを取得する

			j->Update();
		}

		// コンソール上で確認したいことは以下に記入


		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}