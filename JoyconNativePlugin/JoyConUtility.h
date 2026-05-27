#pragma once

#include "JoyConTypes.h"

/*
*	役割
*	生データを加工する関数集
*/

namespace JoyConUtility
{
	// 下ボタンが押されているか取得する関数
	inline bool GetButtonDpadDown(const JoyConRawInput& input)
	{
		return (input.data[5] & 0x01) != 0;
	}
}