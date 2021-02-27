#include "dataSource.h"
#include "DxLib.h"

DataSource::DataSource() {
	player = LoadGraph("resource/organism/player.png");
	mapChip = LoadGraph("resource/map/mapchip.png");
	actionUI = LoadGraph("resource\\UI\\actionUI.png");
	enemy1 = LoadGraph("resource/organism/enemy_1.png");
	weapon1 = LoadGraph("resource/organism/knife.png");
}

DataSource::~DataSource() {
	DeleteGraph(player);
	DeleteGraph(mapChip);
	DeleteGraph(actionUI);
	DeleteGraph(enemy1);
	DeleteGraph(weapon1);
}

int DataSource::playerGraph() {
	return player;
}

int DataSource::mapChipGraph() {
	return mapChip;
}
