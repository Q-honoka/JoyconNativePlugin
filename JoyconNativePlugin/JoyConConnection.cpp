#include "JoyConConnection.h"

/// <summary>
/// コンストラクタ
/// </summary>
JoyConConnection::JoyConConnection() :
	successInit(false),
	devices()
{
	// hidapiの初期化
	if (hid_init() != 0)
	{
		successInit = false;
	}

	successInit = true;
}