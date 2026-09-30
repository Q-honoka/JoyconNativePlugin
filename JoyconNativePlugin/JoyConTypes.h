#pragma once

/*
*	Joy-Conの共通データ
*/

#include <cstdint>
#include <array>

// コントローラーの種類を表す列挙子
enum class ControllerType
{
	JOYCON_LEFT,	// 左Joy-Con
	JOYCON_RIGHT,	// 右Joy-Con
};

// スティックの傾き方向を表す列挙子
// （SL, SYNC, SRが上になるように横向きで持った時の方向）
enum class StickDirection
{
	DIR_UP,			// 上
	DIR_UPRIGHT1,	// 右上
	DIR_RIGHT,		// 右
	DIR_DOWNRIGHT,	// 右下
	DIR_DOWN,		// 下
	DIR_DOWNLEFT,	// 左下
	DIR_LEFT,		// 左
	DIR_UPLEFT,		// 左上
	DIR_CENTER,		// 中央
};

// バッテリー状態
enum class BatteryState
{
	BATTERY_EMPTY,		// バッテリー切れ
	BATTERY_CRITICAL,	// バッテリー切れ寸前
	BATTERY_LOW,		// バッテリー低い
	BATTERY_MEDIUM,		// バッテリー中程度
	BATTERY_FULL,		// バッテリー満タン
	BATTERY_CHARGING,	// バッテリー充電中
};

// 加工後のデータ（デフォルト）
struct ConvertInputData
{
	bool buttonState[14];		// 各ボタンの状態
	StickDirection stickDir;	// スティックの傾き方向
};

// 加工後のデータ（フルモード）
struct ConvertInputDataFull
{
	int timer;		// タイマー

	BatteryState batteryState;	// バッテリーの状態

	bool buttonState[23];		// ボタンの状態

	float leftStickHorizontal;	// 左スティックの垂直方向の傾き
	float leftStickVertical;	// 左スティックの水平方向の傾き
	float rightStickHorizontal;	// 右スティックの垂直方向の傾き
	float rightStickVertical;	// 右スティックの水平方向の傾き

	float gyro[3];	// ジャイロ
	float accel[3];	// 加速度
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
struct JoyConRawFullInputData
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

	int16_t accelX;	// 加速度X
	int16_t accelY;	// 加速度Y
	int16_t accelZ;	// 加速度Z

	int16_t gyro1;		// ジャイロ1
	int16_t gyro2;		// ジャイロ2
	int16_t gyro3;		// ジャイロ3

	int16_t prevAccelX;	// １つ前の加速度X
	int16_t prevAccelY;	// １つ前の加速度Y
	int16_t prevAccelZ;	// １つ前の加速度Z

	int16_t prevGyro1;		// １つ前のジャイロ1
	int16_t prevGyro2;		// １つ前のジャイロ2
	int16_t prevGyro3;		// １つ前のジャイロ3

	int16_t priorAccelX;	// ２つ前の加速度X
	int16_t priorAccelY;	// ２つ前の加速度Y
	int16_t priorAccelZ;	// ２つ前の加速度Z

	int16_t priorGyro1;	// ２つ前のジャイロ1
	int16_t priorGyro2;	// ２つ前のジャイロ2
	int16_t priorGyro3;	// ２つ前のジャイロ3
};

// アナログスティックの校正値
struct RawStickCalibrationData
{
	std::array<uint16_t, 6> leftStickValue;		// 左スティックの校正値
	std::array<uint16_t, 6> rightStickValue;	// 右スティックの校正値
};

// 6軸モーションの校正値
struct Raw6AxisCalibrationData
{
	std::array<int16_t, 3> accelOffset;			// 加速度のオフセット(X,Y,Zの順)
	std::array<int16_t, 3> accelSensitivity;	// 加速度の感度係数
	std::array<int16_t, 3> gyroOffset;			// ジャイロのオフセット(X,Y,Zの順)
	std::array<int16_t, 3> gyroSensitivity;		// ジャイロの感度係数
};

// 振動に必要な数値情報
struct RumbleParameter
{
	float highBandFrequency;		// 高周波帯域の下位周波数
	float highBandAmplitude;		// 高周波帯域の振幅

	float lowBandFrequency;			// 低周波帯域の周波数
	float lowBandAmplitude;			// 低周波帯域の振幅
};

// エンコード後の振動データ
struct EncodedRumbleData
{
	uint8_t data[4];
};