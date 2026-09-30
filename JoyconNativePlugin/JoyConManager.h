#pragma once
#include "JoyConDevice.h"
#include "JoyConConnection.h"
#include <vector>
#include <thread>

/*
	役割
	複数台のJoy-Conを管理する

	責務
	・プラグインの使用開始/終了処理
	・JoyConの使用開始/終了指示

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
	bool Initialize();	// プラグインの開始処理を行う
	void Finalize();	// プラグインの終了処理を行う
	uint32_t Connected();	// Joy-Conと接続する
	void DisConnect(uint32_t id);		// Joy-Conとの接続を解除する

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