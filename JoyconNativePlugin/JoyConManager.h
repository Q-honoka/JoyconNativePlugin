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
	void Update();		// すべてのJoy-Conの入力データを更新する

	// Joy-Conのデータを渡す関数
	bool IsButtonDpadDown();		// 下ボタン

	// コピーガード
	JoyConManager(const JoyConManager& other) = delete;
	JoyConManager& operator=(const JoyConManager& other) = delete;

private:
	JoyConManager();	// コンストラクタ
	bool SetFullReportMode(hid_device* hdl);	// フルデータ取得モードに変更するサブコマンドを送信する
	std::vector<std::unique_ptr<JoyConDevice>> joycons;	// Joy-Con配列

	std::thread updateThread;	// 更新スレッド
	bool isRunning;			// 別スレッドが稼働中か（true：稼働中, false：稼働していない）
};