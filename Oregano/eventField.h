#pragma once
#include "inputProcess.h"
#include "mapDraw.h"

class EventField {
private:
	Input& input;
	MapDraw& map;

	void getFieldItem();

public:
	static bool event;
	static int coin;

	EventField(Input& input, MapDraw& map);

	void update();

	bool getEventCoordinate(const int& mapX, const int& mapY, const int& cX, const int& cY);
};
