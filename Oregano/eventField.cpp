#include "eventField.h"
#include "constant.h"
#include "mapDraw.h"
#include "DxLib.h"

EventField::EventField(Input& input, EventBase& event) : input(input), event(event) {
	eventFlag = false;
	coin = 0;
}

void EventField::getFieldItem() {
	if (input.X && input.moveDirection == UP && event.getEventCoordinate(8, 7, 12, 24) && coin < 10) {
		coin += 10;
		eventFlag = true;
	}
}

void EventField::update() {
	getFieldItem();
	DrawFormatString(300, 0, GetColor(130, 130, 255), "イベント:%d, コイン:%d, 向き:%d, T%d",
	                 this->eventFlag, coin, input.moveDirection,
	                 event.getEventCoordinate(8, 7, 12, 24), false);
	DrawFormatString(100, 0, GetColor(255, 0, 0), "cx:%d, cy:%d",
	                 event.centralPlayerPosition(MAP_X), event.centralPlayerPosition(MAP_Y), false);
}
