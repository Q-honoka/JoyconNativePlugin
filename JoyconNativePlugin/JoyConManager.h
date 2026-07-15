#pragma once
#include "JoyConDevice.h"
#include <vector>
#include <thread>

/*
	役割
	複数台のJoy-Conを管理する

	責務
	・HIDAPIを使用してHIDデバイスを列挙する
	・列挙した結果からJoy-Conを判定して、JoyConDeviceを生成する
	・Joy-Conとの接続をする
	・生成したJoyConDeviceを配列で保持する

	情報
	・JoyConDevice配列
	・更新スレッド
	・スレッドが稼働中かどうか
*/

struct JoyConRawInput;

class JoyConManager
{
public:
	static JoyConManager& GetInstance();	// インスタンスを渡す
	void Initialize();	// Joy-Conの列挙と、JoyConDeviceの生成を行う
	void Finalize();	// すべてのJoy-Conを切断する

	bool CompleteInitialize() const;	// 初期化処理が終わっているか返す
	const int AcquireJoyCon(bool isLeft);		// 未使用のJoyConを返す
	bool ReleaseJoyCon(const int id);			// 使用中のJoy-Conを未使用にする
	bool IsValid(int id);						// 有効なidかどうかを返す
	// Joy-Conのデータを渡す関数
	bool IsButtonPressed(int index, ButtonKind kind);	// 引数で指定されたJoy-Conのボタンが押されたか返す

	// コピーガード
	JoyConManager(const JoyConManager& other) = delete;
	JoyConManager& operator=(const JoyConManager& other) = delete;

private:
	JoyConManager();	// コンストラクタ
	void Update();		// すべてのJoy-Conの入力データを更新する
	bool SetFullReportMode(hid_device* hdl);	// フルデータ取得モードに変更するサブコマンドを送信する
	std::vector<std::unique_ptr<JoyConDevice>> joycons;	// Joy-Con配列

	std::thread updateThread;	// 更新スレッド
	bool isRunning;			// 別スレッドが稼働中か（true：稼働中, false：稼働していない）
	bool completeInit;		// 初期化が終わっているか（true：終わっている, false：終わっていない）
	int waitSeconds;	// 接続待機時間（秒）
};