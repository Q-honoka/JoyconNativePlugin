#pragma once

#include "JoyConTypes.h"
#include "JoyConUtilityData.h"
#include "ButtonMaps.h"

/*
*	役割
*	生データを加工する関数集
*/

/// <summary>
/// バッテリーデータを加工する
/// </summary>
/// <param name="data">バッテリーの生データ</param>
/// <returns>バッテリーの状態を表す列挙子</returns>
inline BatteryState ProcessBatteryData(const uint8_t data)
{
	uint8_t battery = (data >> 4) & 0x0F;
	// データの数値に対応したバッテリーの状態を返す
	switch (battery)
	{
	case BATTERY_FULL_VALUE:
		return BatteryState::BATTERY_FULL;
	case BATTERY_MEDIUM_VALUE:
		return BatteryState::BATTERY_MEDIUM;
	case BATTERY_LOW_VALUE:
		return BatteryState::BATTERY_LOW;
	case BATTERY_CRITICAL_VALUE:
		return BatteryState::BATTERY_CRITICAL;
	case BATTERY_EMPTY_VALUE:
		return BatteryState::BATTERY_EMPTY;
	}

	return BatteryState::BATTERY_ERROR;
}

/// <summary>
/// ボタンデータを加工する
/// </summary>
/// <param name="data">生データ</param>
/// <param name="state">加工後のデータの格納先の先頭アドレス</param>
inline void ProcessButtonData(const std::array<uint8_t, 3>& data, bool* state)
{
	// ボタン対応表の数繰り返す
	for (auto& map : fullModeMaps)
	{
		bool isPressed = (data[map.index] & map.mask) != 0;

		// ボタンが押されていた場合、その位置のフラグを true にする
		if (isPressed)
		{
			state[(int)map.type] = true;
		}
	}
}

/// <summary>
/// スティックデータを加工する
/// </summary>
/// <param name="horizontalData">垂直方向のデータ</param>
/// <param name="verticalData">水平方向のデータ</param>
/// <param name="processHorizontal">垂直方向のデータの格納先</param>
/// <param name="processVertical">水平方向のデータの格納先</param>
/// <param name="cab">校正値</param>
inline void ProcessStickHorizontalData(const uint16_t horizontalData, const uint16_t verticalData, float* processHorizontal, float processVertical, StickCalibrationData cab)
{

}