#pragma once
#include "JoyConDevice.h"
#include <vector>

/*
	役割
	複数台のJoy-Conを管理する

	責務
	・HIDAPIを使用してHIDデバイスを列挙する
	・列挙した結果からJoy-Conを判定して、JoyConDeviceを生成する
	・生成したJoyConDeviceを配列で保持する

	情報
	・JoyConDevice配列
*/

class JoyConManager
{
public:
	void Initialize();	// Joy-Conの列挙と、JoyConDeviceの生成を行う
	void Finalize();	// すべてのJoy-Conを切断する
private:
	std::vector<JoyConDevice> joycons;
};