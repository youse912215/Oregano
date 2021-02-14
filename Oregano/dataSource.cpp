#include "dataSource.h"
#include "DxLib.h"

DataSource::DataSource() {
	player = LoadGraph("resource/charactor/player.png");
	mapChip = LoadGraph("resource/map/mapchip.png");
}

DataSource::~DataSource() {
	DeleteGraph(player);
	DeleteGraph(mapChip);
}

int DataSource::playerGraph() {
	return player;
}

int DataSource::mapChipGraph() {
	return mapChip;
}
