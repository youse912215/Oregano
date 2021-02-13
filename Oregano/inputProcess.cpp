#include "DxLib.h"
#include "mapDraw.h"
#include "inputProcess.h"

char Input::keys[256] = {0};
char Input::oldkeys[256] = {0};

Input::Input() {
}

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
void Input::moving_process(const bool& collisionLeft, const bool& collisionRight,
                           const bool& collisionUp, const bool& collisionDown) {
	if (keys[KEY_INPUT_LEFT]) {
		MapDraw::mapX -= MOVING_DISTANCE;
		if (collisionLeft) MapDraw::mapX += MOVING_DISTANCE;
	}
	if (keys[KEY_INPUT_RIGHT]) {
		MapDraw::mapX += MOVING_DISTANCE;
		if (collisionRight) MapDraw::mapX -= MOVING_DISTANCE;
	}
	if (keys[KEY_INPUT_UP]) {
		MapDraw::mapY -= MOVING_DISTANCE;
		if (collisionUp) MapDraw::mapY += MOVING_DISTANCE;
	}
	if (keys[KEY_INPUT_DOWN]) {
		MapDraw::mapY += MOVING_DISTANCE;
		if (collisionDown) MapDraw::mapY -= MOVING_DISTANCE;
	}

	DrawFormatString(0, 150, GetColor(255, 255, 120), "%d   %d",
	                 collisionLeft, collisionRight, false);
	DrawFormatString(0, 135, GetColor(255, 255, 120), "  %d",
	                 collisionUp, false);
	DrawFormatString(0, 165, GetColor(255, 255, 120), "  %d",
	                 collisionDown, false);
}
