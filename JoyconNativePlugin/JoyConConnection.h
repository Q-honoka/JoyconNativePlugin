#pragma once

#include <unordered_map>
#include <unordered_set>
#include <atomic>
#include <string>
#include "hidapi.h"
#include "JoyConTypes.h"

/*
*	役割
*	Joy-ConとBluetoothを用いた通信を行う
* 
*	責務
*	・HIDAPIを使用してJoy-Conとの接続を行う
*	・Joy-Conの入力データを取得する
*	・Joy-Conにサブコマンドを送信する
*	・Joy-Conとの接続を切断する
* 
*	情報
* 	
*/

// デバイスIDの型
using DeviceID = uint32_t;

class JoyConConnection
{
public:
	JoyConConnection();	// コンストラクタ
	DeviceInfo ConnectionJoyCon();	// コントローラーと接続する
	DeviceInfo ConnectionJoyCon(bool isLeft);		// コントローラーと接続する（左右を指定）
	void DisconnectionController(uint32_t id);		// コントローラーの切断処理
	bool SetFullReportMode(uint32_t id);	// 入力レポートをフルモードにする
	bool GetRawInputData(uint32_t id, JoyConRawDefaultInputData& inputData);	// コントローラーの最新データを取得する（デフォルトモード+Joy-Con）
	bool GetRawInputData(uint32_t id, RawFullInputData& inputData);				// コントローラーの最新データを取得する（フルモード）
	bool GetRawStickCalibrationData(uint32_t id, RawStickCalibrationData& calibrationData);	// スティックの校正値を取得する
	bool GetRaw6AxisCalibrationData(uint32_t id, Raw6AxisCalibrationData& calibrationData);	// 6軸モーションの校正値を取得する
	bool SuccessInit() const;		// HIDAPIの初期化に成功したか
	// 振動を有効にする
	// 振動データを送信する

private:
	std::atomic<DeviceID> nextDeviceID;		// デバイスID
	bool successInit;	// 初期化に成功したか
	std::unordered_map<DeviceID, hid_device*> devices;		// 接続しているデバイス
	std::unordered_set<std::string> devicePaths;			// 接続しているデバイスのパス

	DeviceID CreateDeviceID();		// デバイスIDの作成
};