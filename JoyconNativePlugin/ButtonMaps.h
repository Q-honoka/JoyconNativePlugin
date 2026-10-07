#pragma once

#include "JoyConTypes.h"

// ボタンを共通型に変換する際に必要な情報
struct ButtonMap
{
	int index;			// インデックス
	uint8_t mask;		// マスク
	ButtonType type;	// 種類	
};

// デフォルトモードのボタン対応表（コントローラータイプ：左）
ButtonMap defaultModeLeftMaps[] =
{
	{0, 0x01, ButtonType::BUTTON_DOWN},
	{0, 0x02, ButtonType::BUTTON_RIGHT},
	{0, 0x04, ButtonType::BUTTON_LEFT},
	{0, 0x08, ButtonType::BUTTON_UP},
	{0, 0x10, ButtonType::BUTTON_SL},
	{0, 0x20, ButtonType::BUTTON_SR},

	{1, 0x01, ButtonType::BUTTON_MINUS},
	{1, 0x02, ButtonType::BUTTON_PLUS},
	{1, 0x04, ButtonType::BUTTON_L_STICK},
	{1, 0x08, ButtonType::BUTTON_R_STICK},
	{1, 0x10, ButtonType::BUTTON_HOME},
	{1, 0x20, ButtonType::BUTTON_CAPTURE},
	{1, 0x40, ButtonType::BUTTON_L},
	{1, 0x80, ButtonType::BUTTON_ZL}
};

// デフォルトモードのボタン対応表（コントローラータイプ：右）
ButtonMap defaultModeRightMaps[] =
{
	{0, 0x01, ButtonType::BUTTON_B},
	{0, 0x02, ButtonType::BUTTON_A},
	{0, 0x04, ButtonType::BUTTON_Y},
	{0, 0x08, ButtonType::BUTTON_X},
	{0, 0x10, ButtonType::BUTTON_SL},
	{0, 0x20, ButtonType::BUTTON_SR},

	{1, 0x01, ButtonType::BUTTON_MINUS},
	{1, 0x02, ButtonType::BUTTON_PLUS},
	{1, 0x04, ButtonType::BUTTON_L_STICK},
	{1, 0x08, ButtonType::BUTTON_R_STICK},
	{1, 0x10, ButtonType::BUTTON_HOME},
	{1, 0x20, ButtonType::BUTTON_CAPTURE},
	{1, 0x40, ButtonType::BUTTON_R},
	{1, 0x80, ButtonType::BUTTON_ZR}
};

// フルモードのボタン対応表
ButtonMap fullModeMaps[] =
{
	{0, 0x01, ButtonType::BUTTON_Y},
	{0, 0x02, ButtonType::BUTTON_X},
	{0, 0x04, ButtonType::BUTTON_B},
	{0, 0x08, ButtonType::BUTTON_A},
	{0, 0x10, ButtonType::BUTTON_SR},
	{0, 0x20, ButtonType::BUTTON_SL},
	{0, 0x40, ButtonType::BUTTON_R},
	{0, 0x80, ButtonType::BUTTON_ZR},

	{1, 0x01, ButtonType::BUTTON_MINUS},
	{1, 0x02, ButtonType::BUTTON_PLUS},
	{1, 0x04, ButtonType::BUTTON_R_STICK},
	{1, 0x08, ButtonType::BUTTON_L_STICK},
	{1, 0x10, ButtonType::BUTTON_HOME},
	{1, 0x20, ButtonType::BUTTON_CAPTURE},

	{2, 0x01, ButtonType::BUTTON_DOWN},
	{2, 0x02, ButtonType::BUTTON_UP},
	{2, 0x04, ButtonType::BUTTON_RIGHT},
	{2, 0x08, ButtonType::BUTTON_LEFT},
	{2, 0x10, ButtonType::BUTTON_SR},
	{2, 0x20, ButtonType::BUTTON_SL},
	{2, 0x40, ButtonType::BUTTON_L},
	{2, 0x80, ButtonType::BUTTON_ZL}
};