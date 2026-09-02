#pragma once

#include <unordered_map>
#include <unordered_set>
#include <optional>
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
	~JoyConConnection();	// デストラクタ
	DeviceInfo ConnectionController();	// コントローラーと接続する
	DeviceInfo ConnectionController(ControllerType type);		// コントローラーと接続する（左右を指定）
	void DisconnectionController(DeviceID id);		// コントローラーの切断処理
	bool SetFullReportMode(DeviceID id);	// フルレポートモードのサブコマンドを送信する
	bool GetRawInputData(DeviceID id, JoyConRawDefaultInputData& inputData);	// コントローラーの最新データを取得する（デフォルトモード+Joy-Con）
	bool GetRawInputData(DeviceID id, JoyConRawFullInputData& inputData);		// コントローラーの最新データを取得する（フルモード）
	bool GetRawStickCalibrationData(DeviceID id, RawStickCalibrationData& calibrationData);	// スティックの校正値を取得する
	bool GetRaw6AxisCalibrationData(DeviceID id, Raw6AxisCalibrationData& calibrationData);	// 6軸モーションの校正値を取得する
	bool SuccessInit() const;		// HIDAPIの初期化に成功したか
	// 振動を有効にする
	// 振動データを送信する

private:
	struct ControllerInfo
	{
		hid_device* handle;		// デバイスハンドル
		std::string path;		// パス
		uint8_t packetNumber;	// パケット番号
	};
	std::atomic<DeviceID> nextDeviceID;		// デバイスID
	bool successInit;	// 初期化に成功したか
	std::unordered_map<DeviceID, ControllerInfo> devices;		// 接続しているデバイス
	std::unordered_set<std::string> devicePaths;			// 接続しているデバイスのパス

	DeviceID CreateDeviceID();		// デバイスIDの作成
	int GetProductID(ControllerType type);		// プロダクトIDを取得する
	ControllerType GetControllerType(int productID);	// コントローラーの種類を取得する
	DeviceInfo ConnectionControllerImpl(std::optional<ControllerType> requestType);	// コントローラーと接続する内部関数
};