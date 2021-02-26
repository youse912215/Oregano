#include "eventBase.h"
#include "constant.h"
#include "DxLib.h"

int EventBase::gameScene = TITLE_SCENE;
bool EventBase::night = false;

EventBase::EventBase(int graph) : MapDraw(graph) {
	gameTime = GAME_HOUR * 19; //初期時間は12時
}

/// <summary>
/// 夜の状態を変更(4時から20時までは日中として、false状態にする)
/// </summary>
void EventBase::changeTime() {
	night = (gameTime >= GAME_HOUR * 4 && gameTime <= GAME_HOUR * 20) ? false : true;
}

/// <summary>
/// ゲーム時間起動
/// </summary>
void EventBase::moveGameTime() {
	gameTime = gameTime <= GAME_HOUR * 24 ? ++gameTime : 0; //24時になったら、0時に変更
}

/// <summary>
/// プレイヤーのxまたはyの中心座標を取得
/// </summary>
/// <param name="center">xまたはy</param>
int EventBase::centralPlayerPosition(int center) {
	if (center == POSITION_X) {
		return (mapX / BLOCK_SIZE) % AREA_WIDTH;
	}
	return ((mapY - BLOCK_SIZE / 4) / BLOCK_SIZE) % AREA_HEIGHT;
}

/// <summary>
/// 現在のマップ座標を取得
/// </summary>
/// <param name="current">xまたはy</param>
int EventBase::currentMapPosition(int current) {
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
	return (currentMapPosition(POSITION_X) == mapX)
		&& (currentMapPosition(POSITION_Y) == mapY)
		&& (centralPlayerPosition(POSITION_X) == cX)
		&& (centralPlayerPosition(POSITION_Y) == cY);
}

void EventBase::update() {
	moveGameTime(); //ゲーム時間起動
	changeTime(); //夜の状態を変更

	DrawFormatString(WIN_WIDTH - 300, WIN_HEIGHT - 15, GetColor(255, 0, 0), "TIME:%d, 夜:%d",
	                 gameTime, night, false);
}
