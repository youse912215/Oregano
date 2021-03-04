#pragma once
#include "mapDraw.h"

class EventBase : public MapDraw {
private:

public:
	static int gameScene; //ゲームシーン

	EventBase();

	int blockAreaPos(int center); //現在のプレイヤーの中央座標取得
	int currentMapPos(int current); //現在のマップ座標を取得

	bool getEventCoordinate(const int& mapX, const int& mapY, const int& cX, const int& cY); //イベント座標の真偽

	void update(); //更新処理
};
