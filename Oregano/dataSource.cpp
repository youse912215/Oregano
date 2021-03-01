#include "dataSource.h"
#include "DxLib.h"

DataSource::DataSource() {
	/* ‰æ‘œ */
	player = LoadGraph("resource/organism/player.png");
	mapChip = LoadGraph("resource/map/mapchip.png");
	actionUI = LoadGraph("resource\\UI\\actionUI.png");
	enemyGraph = LoadGraph("resource/organism/enemy_1.png");
	knifeGraph = LoadGraph("resource/organism/knife.png");
	slashGraph = LoadGraph("resource/organism/slash.png");
	shieldGraph = LoadGraph("resource/organism/shield.png");
}

DataSource::~DataSource() {
	DeleteGraph(player);
	DeleteGraph(mapChip);
	DeleteGraph(actionUI);
	DeleteGraph(enemyGraph);
	DeleteGraph(knifeGraph);
	DeleteGraph(slashGraph);
	DeleteGraph(shieldGraph);
}

int DataSource::playerGraph() {
	return player;
}

int DataSource::mapChipGraph() {
	return mapChip;
}
