#pragma once
#include "JoyConDevice.h"
#include "JoyConConnection.h"
#include <vector>
#include <thread>

/*
	役割
	複数台のJoy-Conを管理する

	責務
	・

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
	bool Initialize();	// Joy-Conの列挙と、JoyConDeviceの生成を行う
	void Finalize();	// すべてのJoy-Conを切断する

	// Joy-Conのデータを渡す関数

	// コピーガード
	JoyConManager(const JoyConManager& other) = delete;
	JoyConManager& operator=(const JoyConManager& other) = delete;

private:
	JoyConManager();	// コンストラクタ
	void Update();		// すべてのJoy-Conの入力データを更新する
	std::vector<std::unique_ptr<JoyConDevice>> joycons;	// Joy-Con配列

	JoyConConnection joyconConnection;		// Joy-Conとの接続クラスのインスタンス
	std::thread updateThread;	// 更新スレッド
	bool isRunning;			// 別スレッドが稼働中か（true：稼働中, false：稼働していない）
};