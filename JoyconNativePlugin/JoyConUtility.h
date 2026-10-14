#pragma once

#include "JoyConTypes.h"
#include "JoyConUtilityData.h"

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
	// データの数値に対応したバッテリーの状態を返す
	switch (data)
	{
	case BUTTERY_FULL_VALUE:
		return BatteryState::BATTERY_FULL;
	case BUTTERY_MEDIUM_VALUE:
		return BatteryState::BATTERY_MEDIUM;
	case BUTTERY_LOW_VALUE:
		return BatteryState::BATTERY_LOW;
	case BUTTERY_CRITICAL_VALUE:
		return BatteryState::BATTERY_CRITICAL;
	case BUTTERY_EMPTY_VALUE:
		return BatteryState::BATTERY_EMPTY;
	}

	return BatteryState::BATTERY_ERROR;
}