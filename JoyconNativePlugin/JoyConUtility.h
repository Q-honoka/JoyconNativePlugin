#pragma once

#include "JoyConTypes.h"

/*
*	役割
*	生データを加工する関数集
*/

// Joy-Con(左)のときに取得できるボタンの種類
const ButtonKind leftButtonKinds[11] =
{
	BUTTON_DOWN,	// 下
	BUTTON_UP,		// 上
	BUTTON_RIGHT,	// 右
	BUTTON_LEFT,	// 左
	BUTTON_SR,		// SR
	BUTTON_SL,		// SL
	BUTTON_L,		// L
	BUTTON_ZL,		// ZL
	BUTTON_MINUS,	// マイナス
	BUTTON_STICK,	// スティック押し込み
	BUTTON_CAPTURE,	// キャプチャ
};

// Joy-Con(右)のときに取得できるボタンの種類
const ButtonKind rightButtonKind[11] =
{
	BUTTON_Y,		// Y
	BUTTON_X,		// X
	BUTTON_A,		// A
	BUTTON_B,		// B
	BUTTON_SR,		// SR
	BUTTON_SL,		// SL
	BUTTON_R,		// R
	BUTTON_ZR,		// ZR
	BUTTON_PLUS,	// プラス
	BUTTON_STICK,	// スティック押し込み
	BUTTON_HOME		// ホーム
};

namespace JoyConUtility
{
	/*
	*	ボタンの取得関数
	*	data[3] -> Joy-Con(R)
	*	bit0:Y, bit1:X, bit2:B, bit3:A, bit4:SR, bit5:SL, bit6:R, bit7:ZR
	*
	*	data[4] -> 共通・その他
	*	bit0:マイナス, bit1:プラス,
	*	bit2:右スティック押し込み, bit3:左スティック押し込み,
	*	bit4:HOME, bit5:キャプチャ,
	*	bit7:充電グリップ接続フラグ
	*
	*	data[5] -> Joy-Con(L)
	*	bit0:下, bit1:上, bit2:右, bit3:左, bit4:SR, bit5:SL, bit6:L, bit7:ZL
	*/

	/// <summary>
	/// 指定のボタンが押されたか返す
	/// </summary>
	/// <param name="input">生データ</param>
	/// <param name="kind">ボタンの種類</param>
	/// <returns>押されたかどうか(true：押された, false：押されていない)</returns>
	inline bool IsButtonPressed(const JoyConRawInput& input, ButtonKind kind, bool isLeft)
	{
		// ボタンの種類とコントローラーの左右が適切な組み合わせか調べる
		bool isSucess = false;
		if (isLeft)
		{
			for (int i = 0; i < 11; i++)
			{
				// 一致する種類があれば適切な組み合わせ
				if (kind == leftButtonKinds[i]) isSucess = true;
			}
		}
		else
		{
			for (int i = 0; i < 11; i++)
			{
				// 一致する種類があれば適切な組み合わせ
				if (kind == rightButtonKind[i])isSucess = true;
			}
		}

		// 適切な組み合わせでなければfalseを返す
		if (!isSucess) return false;

		// 調べるデータを特定する
		int dataIndex = -1;
		if (ButtonKind::BUTTON_MINUS <= kind)
		{
			// 固有ボタンは4番データを調べる
			dataIndex = 4;
		}
		else
		{
			// 左Joy-Conなら5番データを、右Joy-Conなら3番データを調べる
			dataIndex = isLeft ? 5 : 3;
		}

		// 調べるビットを特定する
		int bitNum = -1;

		// ボタンに合わせて種類を変更する(共通・その他は未実装)
		// スティック押し込みのビットは左右で異なるため、フラグで分岐する
		if (kind == BUTTON_STICK)
		{
			// 左なら3番, 右なら2番目のビットを調べる
			bitNum = isLeft ? 3 : 2;
		}
		else
		{
			// スティック押し込み以外のボタンはSwitch文で特定する
			switch (kind)
			{
			case BUTTON_Y:
			case BUTTON_DOWN:
			case BUTTON_MINUS:
				bitNum = 0;
				break;

			case BUTTON_X:
			case BUTTON_UP:
			case BUTTON_PLUS:
				bitNum = 1;
				break;

			case BUTTON_B:
			case BUTTON_RIGHT:
				bitNum = 2;
				break;

			case BUTTON_A:
			case BUTTON_LEFT:
				bitNum = 3;
				break;

			case BUTTON_SR:
			case BUTTON_HOME:
				bitNum = 4;
				break;

			case BUTTON_SL:
			case BUTTON_CAPTURE:
				bitNum = 5;
				break;

			case BUTTON_R:
			case BUTTON_L:
				bitNum = 6;
				break;

			case BUTTON_ZR:
			case BUTTON_ZL:
				bitNum = 7;
				break;

			default:
				break;
			}
		}

		// 取得位置が特定できなかった場合は、falseを返す
		if (dataIndex == -1 || bitNum == -1) return false;

		return (input.data[dataIndex] & (1 << bitNum)) != 0;
	}
}