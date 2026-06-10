#pragma once

/*
*	Joy-Conの共通データ
*/

// Joy-Conから取得した生データ
struct JoyConRawInput
{
	unsigned char data[64];
	/*
	[0]		データの種類
	[1]		フレームカウンタ
	[2]		バッテリーと接続状態
	[3～5]	ボタンデータ
	[6～11]	システムデータ（開発では使用しない）
	[12]	振動応答
	[13～18]スティックデータ
	[19～48]モーションセンサー
	*/
};

// ボタンの種類
enum ButtonKind
{
	BUTTON_DOWN,	// 下
	BUTTON_UP,		// 上
	BUTTON_RIGHT,	// 右
	BUTTON_LEFT,	// 左
	BUTTON_Y,		// Y
	BUTTON_X,		// X
	BUTTON_A,		// A
	BUTTON_B,		// B
	BUTTON_SR,		// SR
	BUTTON_SL,		// SL
	BUTTON_R,		// R
	BUTTON_L,		// L
	BUTTON_ZR,		// ZR
	BUTTON_ZL,		// ZL
	BUTTON_MINUS,	// マイナス
	BUTTON_PLUS,	// プラス
	BUTTON_STICK,	// スティック押し込み
	BUTTON_CAPTURE,	// キャプチャ
	BUTTON_HOME		// ホーム
};