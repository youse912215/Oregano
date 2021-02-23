#pragma once
#include "mapDraw.h"

class EventBase : public MapDraw {
private:


public:
	int centralPlayerPosition(int center); //現在のプレイヤーの中央座標取得
	int currentMapPosition(int current); //現在のマップ座標を取得
	static int gameScene; //ゲームシーン
	static int gameTime; //ゲーム時間

	EventBase(int graph = 0);
	bool getEventCoordinate(const int& mapX, const int& mapY, const int& cX, const int& cY); //イベント座標の真偽
};
