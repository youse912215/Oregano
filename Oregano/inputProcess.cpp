#include "DxLib.h"
#include "mapDraw.h"
#include "inputProcess.h"

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
void Input::moving_process(const int& collisionLeftUp, const int& collisionRightUp,
                           const int& collisionLeftDown, const int& collisionRightDown,
                           const int& collisionCenterLeft, const int& collisionCenterRight,
                           const int& collisionCenterUp, const int& collisionCenterDown) {

	//input_info();
	if (keys[KEY_INPUT_LEFT]) {
		MapDraw::map_x -= MOVING_DISTANCE;
		if ((collisionLeftUp == 1 && collisionCenterLeft == 1)
			|| (collisionLeftDown == 1 && collisionCenterLeft == 1))
			MapDraw::map_x += MOVING_DISTANCE;
	}
	if (keys[KEY_INPUT_RIGHT]) {
		MapDraw::map_x += MOVING_DISTANCE;
		if ((collisionRightUp == 1 && collisionCenterRight == 1)
			|| (collisionRightDown == 1 && collisionCenterRight == 1))
			MapDraw::map_x -= MOVING_DISTANCE;
	}
	if (keys[KEY_INPUT_UP]) {
		MapDraw::map_y -= MOVING_DISTANCE;
		if ((collisionLeftUp == 1 && collisionCenterUp == 1)
			|| (collisionRightUp == 1 && collisionCenterUp == 1))
			MapDraw::map_y += MOVING_DISTANCE;
	}
	if (keys[KEY_INPUT_DOWN]) {
		MapDraw::map_y += MOVING_DISTANCE;
		if ((collisionLeftDown == 1 && collisionCenterDown == 1)
			|| (collisionRightDown == 1 && collisionCenterDown == 1))
			MapDraw::map_y -= MOVING_DISTANCE;
	}

	DrawFormatString(0, 150, GetColor(255, 255, 120), "%d, %d, %d, %d",
	                 collisionLeftUp, collisionRightUp, collisionLeftDown, collisionRightDown, false);
}
