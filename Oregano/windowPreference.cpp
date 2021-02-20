#include "DxLib.h"
#include "constant.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "Oregano -Planted Seeds-";

void windowSettingOutLoop() {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);
}

void windowSettingInLoop() {
	ScreenFlip(); //(ダブルバッファ)裏面
	WaitTimer(20); //20ミリ秒待機(疑似60FPS)
}
