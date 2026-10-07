#pragma once

#include "JoyConTypes.h"
#include "ButtonMaps.h"

/*
*	役割
*	生データを加工する関数集
*/

inline uint32_t PackButtonState(DeviceInputMode mode, ControllerType type, uint8_t* buffer)
{
	uint32_t state = 0;

	// デフォルトモード
	if (DeviceInputMode::MODE_DEFAULT == mode)
	{
		// コントローラーの種類に応じて対応表を変える
		if (type == ControllerType::JOYCON_LEFT)
		{
			for (int i = 0; i < 14; i++)
			{
				if (buffer[defaultModeLeftMaps[i].index] & defaultModeLeftMaps[i].mask)
				{
					state |= 1u << static_cast<uint32_t>(defaultModeLeftMaps[i].type);
				}
			}
		}
		else
		{
			for (int i = 0; i < 14; i++)
			{
				if (buffer[defaultModeRightMaps[i].index] & defaultModeRightMaps[i].mask)
				{
					state |= 1u << static_cast<uint32_t>(defaultModeRightMaps[i].type);
				}
			}
		}
	}

	// フルモード
	if (DeviceInputMode::MODE_FULL == mode)
	{
		for (int i = 0; i < 22; i++)
		{
			if (buffer[fullModeMaps[i].index] & fullModeMaps[i].mask)
			{
				state |= 1u << static_cast<uint32_t>(fullModeMaps[i].type);
			}
		}
	}

	return state;
}