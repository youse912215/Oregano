#pragma once
#include "mapDraw.h"

class EventBase : public MapDraw {
private:
	int gameTime; //ゲーム時間

	void changeTime(); //夜の状態を変更
	void moveGameTime();


public:
	static int gameScene; //ゲームシーン
	static bool night; //trueなら夜

	EventBase(int graph = 0); //コンストラクタ

	int centralPlayerPosition(int center); //現在のプレイヤーの中央座標取得
	int currentMapPosition(int current); //現在のマップ座標を取得

	bool getEventCoordinate(const int& mapX, const int& mapY, const int& cX, const int& cY); //イベント座標の真偽

	void update(); //更新処理
};
