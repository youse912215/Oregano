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
void Input::moving_process(const bool& collisionLeftUp, const bool& collisionRightUp,
                           const bool& collisionLeftDown, const bool& collisionRightDown,
                           const bool& collisionCenterLeft, const bool& collisionCenterRight,
                           const bool& collisionCenterUp, const bool& collisionCenterDown) {

	//input_info();
	if (keys[KEY_INPUT_LEFT]) {
		MapDraw::mapX -= MOVING_DISTANCE;
		if ((collisionLeftUp && collisionCenterLeft)
			|| (collisionLeftDown && collisionCenterLeft))
			MapDraw::mapX += MOVING_DISTANCE;
	}
	if (keys[KEY_INPUT_RIGHT]) {
		MapDraw::mapX += MOVING_DISTANCE;
		if ((collisionRightUp && collisionCenterRight)
			|| (collisionRightDown && collisionCenterRight))
			MapDraw::mapX -= MOVING_DISTANCE;
	}
	if (keys[KEY_INPUT_UP]) {
		MapDraw::mapY -= MOVING_DISTANCE;
		if ((collisionLeftUp && collisionCenterUp)
			|| (collisionRightUp && collisionCenterUp))
			MapDraw::mapY += MOVING_DISTANCE;
	}
	if (keys[KEY_INPUT_DOWN]) {
		MapDraw::mapY += MOVING_DISTANCE;
		if ((collisionLeftDown && collisionCenterDown)
			|| (collisionRightDown && collisionCenterDown))
			MapDraw::mapY -= MOVING_DISTANCE;
	}

	DrawFormatString(0, 150, GetColor(255, 255, 120), "%d, %d, %d, %d",
	                 collisionLeftUp, collisionRightUp, collisionLeftDown, collisionRightDown, false);
}
