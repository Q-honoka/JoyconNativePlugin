#pragma once

/*
*	Joy-Conの共通データ
*/

#include <cstdint>
#include <array>

// デバイスのIDを表す型
using DeviceID = uint32_t;

// コントローラーの種類を表す列挙子
enum class ControllerType
{
	JOYCON_LEFT,	// 左Joy-Con
	JOYCON_RIGHT,	// 右Joy-Con
};

// バッテリーの状態を表す列挙子
enum class BatteryState
{
	BATTERY_FULL = 0,		// フル
	BATTERY_MEDIUM = 1,		// 並
	BATTERY_LOW = 2,		// 低い
	BATTERY_CRITICAL = 3,	// 切れそう
	BATTERY_EMPTY = 4,		// 空
	BATTERY_ERROR = 5		// エラー
};

// ボタンの種類を表す列挙子
enum class ButtonType
{
	BUTTON_A = 0,		// Aボタン
	BUTTON_B = 1,		// Bボタン
	BUTTON_X = 2,		// Xボタン
	BUTTON_Y = 3,		// Yボタン
	BUTTON_SR = 4,		// SRボタン
	BUTTON_SL = 5,		// SLボタン
	BUTTON_R = 6,		// Rボタン
	BUTTON_ZR = 7,		// ZRボタン
	BUTTON_MINUS = 8,	// マイナスボタン
	BUTTON_PLUS = 9,	// プラスボタン
	BUTTON_R_STICK = 10,	// Rスティックボタン
	BUTTON_L_STICK = 11, // Lスティックボタン
	BUTTON_HOME = 12,	// HOMEボタン
	BUTTON_CAPTURE = 13,	// CAPTUREボタン
	BUTTON_DOWN = 14,	// 下ボタン（縦持ち）
	BUTTON_UP = 15,		// 上ボタン（縦持ち）
	BUTTON_RIGHT = 16,	// 右ボタン（縦持ち）
	BUTTON_LEFT = 17,	// 左ボタン（縦持ち）
	BUTTON_L = 18,		// Lボタン
	BUTTON_ZL = 19,		// ZLボタン
};

// デバイスの情報
struct DeviceInfo
{
	DeviceID deviceID;		// そのデバイスのID
	ControllerType type;	// コントローラーの種類
	bool isConnected;		// 接続できたか
};

// 取得した生データ（フルモード）
struct JoyConRawFullInputData
{
	uint8_t inputReportID;	// 入力レポートID
	uint8_t timer;			// タイマー

	uint8_t battery;		// バッテリー状態
	uint8_t connection;		// 接続状態

	std::array<uint8_t, 3> buttonState;	// ボタンデータ

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

// 加工後のJoy-Conのデータ（フルモード）
struct JoyConProcessedFullData
{
	BatteryState batteryState;	// バッテリーの状態
	bool buttonState[20];		// ボタンの状態

	float leftStickHorizontalData;	// 左スティックのx方向データ
	float leftStickVerticalData;	// 左スティックのy方向データ
	float rightStickHorizontalData;	// 右スティックのx方向データ
	float rightStickVerticalData;	// 右スティックのy方向データ

	float accX;	// 加速度X
	float accY;	// 加速度Y
	float accZ;	// 加速度Z

	float gyroX;	// ジャイロX
	float gyroY;	// ジャイロY
	float gyroZ;	// ジャイロZ
};

// アナログスティックの校正値
struct StickCalibrationData
{
	uint16_t centerX;	// 中心のX値
	uint16_t centerY;	// 中心のY値

	uint16_t maxX;	// 最大のX値
	uint16_t maxY;	// 最大のY値
	
	uint16_t minX;	// 最小のX値
	uint16_t minY;	// 最小のY値
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