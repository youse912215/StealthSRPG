#include "DxLib.h"
#include "windowPreference.h"
#include "loopProcess.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	window_out_loop(); //ループ外ウィンドウ設定
	if (DxLib_Init() == -1) { return -1; } //DXlibの初期化
	SetDrawScreen(DX_SCREEN_BACK); //(ダブルバッファ)描画先グラフィック領域は裏面を指定

	loop_process(); //ループ内処理

	DxLib_End(); //Dxライブラリ終了処理
	return 0; //正常終了
}
