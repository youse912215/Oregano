#include "DxLib.h"
#include "map_all.h"
#include "input.h"

char Input::keys[256] = {0};
char Input::oldkeys[256] = {0};

void Input::input_info() {
	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; ++i) {
		oldkeys[i] = keys[i];
	}
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
}

/// <summary>
/// 移動処理
/// </summary>
void Input::moving_process() {
	input_info();
	if (keys[KEY_INPUT_LEFT]) {
		Map_all::map_x -= moving_speed;
	}
	if (keys[KEY_INPUT_RIGHT]) {
		Map_all::map_x += moving_speed;
	}
	if (keys[KEY_INPUT_UP]) {
		Map_all::map_y -= moving_speed;
	}
	if (keys[KEY_INPUT_DOWN]) {
		Map_all::map_y += moving_speed;
	}
}
