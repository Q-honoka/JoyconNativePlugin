#include "JoyConManager.h"

constexpr int VENDOR_NINTENDO = 0x057E;		// 任天堂のベンダーID（1406）

constexpr int PRODUCT_JOYCON_L = 0x2006;	// Joy-Con(L)のプロダクトID（8198）
constexpr int PRODUCT_JOYCON_R = 0x2007;	// Joy-Con(R)のプロダクトID（8199）

/// <summary>
/// コンストラクタ
/// </summary>
JoyConManager::JoyConManager() :
	joycons(),
	joyconConnection(),
	updateThread(),
	isRunning(false)
{ }

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
/// Joy-Conの列挙と接続、JoyConDeviceの生成を行う
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
/// すべてのJoy-Conを切断する
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