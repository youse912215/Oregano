#include "eventBase.h"
#include "constant.h"
#include "DxLib.h"

int EventBase::gameScene = TITLE_SCENE;

EventBase::EventBase() {
}

/// <summary>
/// プレイヤーのxまたはyの中心座標を取得
/// </summary>
/// <param name="center">xまたはy</param>
int EventBase::blockAreaPos(int center) {
	if (center == POSITION_X) {
		return (mapX / BLOCK_SIZE) % AREA_WIDTH;
	}
	return ((mapY - QUARTER_BLOCK_SIZE) / BLOCK_SIZE) % AREA_HEIGHT;
}

/// <summary>
/// 現在のマップ座標を取得
/// </summary>
/// <param name="current">xまたはy</param>
int EventBase::currentMapPos(int current) {
	if (current == POSITION_X)
		return mapX / (BLOCK_SIZE * AREA_WIDTH);
	return mapY / (BLOCK_SIZE * AREA_HEIGHT);
}

/// <summary>
/// イベントが発生する座標の真偽を返す
/// </summary>
/// <param name="mapX">マップx座標</param>
/// <param name="mapY">マップy座標</param>
/// <param name="cX">現在のプレイヤーの中心x座標</param>
/// <param name="cY">現在のプレイヤーの中心y座標</param>
/// <returns></returns>
bool EventBase::getEventCoordinate(const int& mapX, const int& mapY, const int& cX, const int& cY) {
	return (currentMapPos(POSITION_X) == mapX)
		&& (currentMapPos(POSITION_Y) == mapY)
		&& (blockAreaPos(POSITION_X) == cX)
		&& (blockAreaPos(POSITION_Y) == cY);
}

void EventBase::update() {
	DrawFormatString(100, 0, GetColor(255, 0, 0), "cx:%d, cy:%d,",
	                 blockAreaPos(POSITION_X), blockAreaPos(POSITION_Y), false);
}
