#include "JoyConManager.h"
#include "hidapi.h"
#include "JoyConTypes.h"
#include "JoyConUtility.h"

constexpr int VENDOR_NINTENDO = 0x057E;		// 任天堂のベンダーID（1406）

constexpr int PRODUCT_JOYCON_L = 0x2006;	// Joy-Con(L)のプロダクトID（8198）
constexpr int PRODUCT_JOYCON_R = 0x2007;	// Joy-Con(R)のプロダクトID（8199）

/// <summary>
/// コンストラクタ
/// </summary>
JoyConManager::JoyConManager() :
	joycons(),
	updateThread(),
	isRunning(false),
	completeInit(false),
	waitSeconds(20)
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
				if (SetFullReportMode(dev))
				{
					printf("サブコマンドの送信成功\n");
					hid_set_nonblocking(dev, 1);
					waitSeconds = 100;
					joycons.emplace_back(std::make_unique<JoyConDevice>(dev, isLeft));
				}
				else
				{
					printf("サブコマンドの送信失敗\n");
				}
			}
		}

		device = device->next;
	}

	hid_free_enumeration(devInfo);

	// スレッドを起動する
	isRunning = true;
	updateThread = std::thread(&JoyConManager::Update, this);

	completeInit = true;
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

/// <summary>
/// フルデータ取得モードに変更するサブコマンドを送信する
/// </summary>
/// <param name="dev">デバイスハンドル</param>
/// <returns>送信結果
/// <para>true：成功</para>
/// <para>false：失敗</para>
/// </returns>
bool JoyConManager::SetFullReportMode(hid_device* dev)
{
	const int RETRY_COUNT = 5;

	// サブコマンドの作成
	unsigned char buf[64] = { 0 };

	static unsigned char timer = 0;

	buf[0] = 0x01;		// レポートID
	buf[1] = timer++;	// タイマー（毎回変える）

	// rumble
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x00;
	buf[5] = 0x00;
	buf[6] = 0x00;
	buf[7] = 0x00;
	buf[8] = 0x00;
	buf[9] = 0x00;

	buf[10] = 0x03;		// サブコマンドID
	buf[11] = 0x30;		// フル入力モード

	// サブコマンドを送信する
	for (int i = 0; i < RETRY_COUNT; i++)
	{
		int result = hid_write(dev, buf, 12);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		// データを仮取得する
		unsigned char readBuf[64] = { 0 };
		int readResult = hid_read_timeout(dev, readBuf, 32, 100);
		//printf("サブコマンドの送信結果 %d, 受信結果 %d\n", result, readResult);

		//for (int i = 0; i < 64; i++)
		//{
		//	printf("%02X ", readBuf[i]);
		//}
		//printf("\n");

		// 応答があったらtrueを返す
		if (0 < result && 
			readBuf[0] == 0x21 && 
			readBuf[13] == 0x80 &&
			readBuf[14] == 0x03)
		{
			return true;
		}

		if (0 < result &&
			readResult > 0 &&
			readBuf[0] == 0x30)
		{
			return true;
		}

		printf("サブコマンドの送信失敗, リトライ回数 %d\n", i);
	}

	return false;
}

/// <summary>
/// 初期化処理が終わっているか返す
/// </summary>
/// <returns>true：初期化が完了している, false：初期化が完了していない</returns>
bool JoyConManager::CompleteInitialize() const
{
	return completeInit;
}

/// <summary>
/// 未使用のJoy-Conを返す
/// </summary>
/// <returns>-1：エラー, 未使用のJoy-Conなし　それ以外の数値：そのJoy-Conの識別ID</returns>
const int JoyConManager::AcquireJoyCon(bool isLeft)
{
	if (joycons.empty()) return -1;

	// 未使用かつ指定されたJoy-Conタイプがあれば識別IDを渡す
	for (int i = 0; i < joycons.size(); ++i)
	{
		if (!joycons[i]->IsActive() == false &&
			joycons[i]->IsLeft() == isLeft)
		{
			joycons[i]->SetActive(true);
			return i;
		}
	}

	return -1;
}

/// <summary>
/// 使用中のJoy-Conを未使用にする
/// </summary>
/// <param name="id">識別ID</param>
/// <returns>true：成功, false：失敗</returns>
bool JoyConManager::ReleaseJoyCon(const int id)
{
	if (!IsValid(id)) return false;

	joycons[id]->SetActive(false);

	return true;
}

/// <summary>
/// 有効なIDかどうかを返す
/// </summary>
/// <param name="id">識別ID</param>
/// <returns>true：有効, false：無効</returns>
bool JoyConManager::IsValid(const int id)
{
	return 0 <= id && 
		id < joycons.size() && 
		joycons[id]->IsActive();
}

/// <summary>
/// 引数で指定されたJoy-Conのボタンが押されたか返す
/// </summary>
/// <param name="index">識別ID</param>
/// <param name="kind">ボタンの種類</param>
/// <returns>押されたかどうか(true：押された, false：押されていない, エラー)</returns>
bool JoyConManager::IsButtonPressed(int id, ButtonKind kind)
{
	if (id < 0 || joycons.size() <= id) return false;
	if (IsValid(id) == false) return false;

	return JoyConUtility::IsButtonPressed(joycons[id]->GetJoyConRawInput(), kind, joycons[id]->IsLeft());
}