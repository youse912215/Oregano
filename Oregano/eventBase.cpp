#include "eventBase.h"

int EventBase::gameScene = GAME_SCENE;

EventBase::EventBase(int graph) : MapDraw(graph) {
}

/// <summary>
/// プレイヤーのxまたはyの中心座標を取得
/// </summary>
/// <param name="center">xまたはy</param>
int EventBase::centralPlayerPosition(int center) {
	if (center == MAP_X) {
		return (mapX / BLOCK_SIZE) % 25;
	}
	return ((mapY - 16) / BLOCK_SIZE) % 25;
}

/// <summary>
/// 現在のマップ座標を取得
/// </summary>
/// <param name="current">xまたはy</param>
int EventBase::currentMapPosition(int current) {
	if (current == MAP_X)
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
	return (currentMapPosition(MAP_X) == mapX)
		&& (currentMapPosition(MAP_Y) == mapY)
		&& (centralPlayerPosition(MAP_X) == cX)
		&& (centralPlayerPosition(MAP_Y) == cY);
}
