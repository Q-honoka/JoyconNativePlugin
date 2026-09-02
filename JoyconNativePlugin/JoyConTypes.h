#pragma once

/*
*	Joy-Conの共通データ
*/

#include <cstdint>
#include <array>

// Joy-Conから取得した生データ
struct JoyConRawInput
{
	unsigned char data[64];
	/*
	[0]		データの種類
	[1]		フレームカウンタ
	[2]		バッテリーと接続状態
	[3～5]	ボタンデータ
	[6～11]	システムデータ（開発では使用しない）
	[12]	振動応答
	[13～18]スティックデータ
	[19～48]モーションセンサー
	*/
};

// コントローラーの種類を表す列挙子
enum class ControllerType
{
	JOYCON_LEFT,	// 左Joy-Con
	JOYCON_RIGHT,	// 右Joy-Con
};

// デバイスの情報
struct DeviceInfo
{
	uint32_t deviceID;		// そのデバイスのID
	ControllerType type;	// コントローラーの種類
	bool isConnected;		// 接続できたか
};

// 取得した生データ（デフォルトモード+Joy-Con）
struct JoyConRawDefaultInputData
{
	uint8_t inputReportID;	// 入力レポートID

	std::array<uint8_t, 2> buttonState;	// ボタンデータ
	uint8_t stickHat;		// スティックハットデータ
};

// 取得した生データ（フルモード）
struct RawFullInputData
{
	uint8_t inputReportID;	// 入力レポートID
	uint8_t timer;			// タイマー

	uint8_t battery;		// バッテリー状態
	uint8_t connection;		// 接続状態

	uint8_t rightButton;	// 右ボタンデータ
	uint8_t sharedButton;	// 共通ボタンデータ
	uint8_t leftButton;		// 左ボタンデータ

	uint16_t leftStickHorizontal;	// 左スティックの上下データ
	uint16_t leftStickVertical;		// 左スティックの左右データ

	uint16_t rightStickHorizontal;	// 右スティックの上下データ
	uint16_t rightStickVertical;	// 右スティックの左右データ

	uint8_t rumble;		// 振動データ

	uint16_t accelX;	// 加速度X
	uint16_t accelY;	// 加速度Y
	uint16_t accelZ;	// 加速度Z

	uint16_t gyro1;		// ジャイロ1
	uint16_t gyro2;		// ジャイロ2
	uint16_t gyro3;		// ジャイロ3

	uint16_t prevAccelX;	// １つ前の加速度X
	uint16_t prevAccelY;	// １つ前の加速度Y
	uint16_t prevAccelZ;	// １つ前の加速度Z

	uint16_t prevGyro1;		// １つ前のジャイロ1
	uint16_t prevGyro2;		// １つ前のジャイロ2
	uint16_t prevGyro3;		// １つ前のジャイロ3

	uint16_t priorAccelX;	// ２つ前の加速度X
	uint16_t priorAccelY;	// ２つ前の加速度Y
	uint16_t priorAccelZ;	// ２つ前の加速度Z

	uint16_t priorGyro1;	// ２つ前のジャイロ1
	uint16_t priorGyro2;	// ２つ前のジャイロ2
	uint16_t priorGyro3;	// ２つ前のジャイロ3
};

// アナログスティックの校正値
struct RawStickCalibrationData
{
	std::array<uint8_t, 9> leftStickValue;	// 左スティックの校正値
	std::array<uint8_t, 9> rightStickValue;	// 右スティックの校正値
};

// 6軸モーションの校正値
struct Raw6AxisCalibrationData
{
	// サイズは不明...
};

// 振動に必要なデータ
struct VibrationData
{

};