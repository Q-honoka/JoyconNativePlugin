// TestJoyconApp.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "JoyconNativePlugin.h"


int main()
{
    if (JoyConInitialize() == false)
    {
        std::cout << "初期化失敗。プログラム終了" << std::endl;
        return 1;
    }

    DeviceID id;
    id = JoyConConnected();

    if (id == 0xFFFFFFFF)
    {
        std::cout << "接続失敗。プログラム終了" << std::endl;
        JoyConFinalize();
        return 1;
    }
    std::cout << "接続成功。" << std::endl;

    switch (GetBatteryState(id))
    {
    case BatteryState::BATTERY_FULL:
        std::cout << "フルバッテリー" << std::endl;
        break;

    case BatteryState::BATTERY_MEDIUM:
        std::cout << "並バッテリー" << std::endl;
        break;

    case BatteryState::BATTERY_LOW:
        std::cout << "低バッテリー" << std::endl;
        break;

    case BatteryState::BATTERY_CRITICAL:
        std::cout << "バッテリー切れそう" << std::endl;
        break;

    case BatteryState::BATTERY_EMPTY:
        std::cout << "空バッテリー" << std::endl;
        break;

    case BatteryState::BATTERY_ERROR:
        std::cout << "バッテリーエラー" << std::endl;
        break;
    }

    std::cin.get();

    JoyConDisConnect(id);
    JoyConFinalize();

    return 0;
}


// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
