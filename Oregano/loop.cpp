#include "DxLib.h"
#include "window_preference.h"
#include "input.h"
#include "player.h"
#include "map_draw.h"
#include "coordinate_confirmation.h"

void loop_process() {
	// ゲームループ
	while (true) {
		// 画面クリア
		ClearDrawScreen();

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break; //終了処理
		Input* input = new Input;
		input->moving_process();
		delete input;
		Map_draw* map_draw = new Map_draw;
		map_draw->drawing_map();
		delete map_draw;
		Player* player = new Player;
		player->draw();
		delete player;
		Coodinate* debug = new Coodinate;
		debug->debug();
		delete debug;

		window_in_roop(); //ループ内ウィンドウ設定
		if (ProcessMessage() == -1) break; //Windowsシステムからくる情報を処理
	}
}
