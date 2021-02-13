#include "eventField.h"
#include "constant.h"
#include "mapDraw.h"
#include "DxLib.h"

int EventField::coin = 0;
bool EventField::event = false;

EventField::EventField(Input& input, MapDraw& map) : input(input), map(map) {
	this->event = false;
}

void EventField::getFieldItem() {
	if (input.X && input.moveDirection == UP && getEventCoordinate(8, 7, 12, 24) && coin < 10) {
		coin += 10;
	}
}

void EventField::update() {
	getFieldItem();
	DrawFormatString(300, 0, GetColor(130, 130, 255), "イベント:%d, コイン:%d, 向き:%d",
	                 this->event, coin, input.moveDirection, false);
	DrawFormatString(100, 0, GetColor(255, 0, 0), "cx:%d, cy:%d",
	                 map.centralPlayerPosition(MAP_X), map.centralPlayerPosition(MAP_Y), false);
}

bool EventField::getEventCoordinate(const int& mapX, const int& mapY, const int& cX, const int& cY) {
	return (map.currentMapPosition(MAP_X) == mapX)
		&& (map.currentMapPosition(MAP_Y) == mapY)
		&& (map.centralPlayerPosition(MAP_X) == cX)
		&& (map.centralPlayerPosition(MAP_Y) == cY);
}
