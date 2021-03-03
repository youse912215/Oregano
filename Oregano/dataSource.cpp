#include "dataSource.h"
#include "DxLib.h"

DataSource::DataSource() {
	/* �摜 */
	player = LoadGraph("resource/organism/player.png");
	mapChip = LoadGraph("resource/map/mapchip.png");
	actionUI = LoadGraph("resource\\UI\\actionUI.png");
	enemyGraph = LoadGraph("resource/organism/enemy_1.png");
	knifeGraph = LoadGraph("resource/organism/knife.png");
	slashGraph = LoadGraph("resource/organism/slash.png");
	shieldGraph = LoadGraph("resource/organism/shield.png");
	red = LoadGraph("resource/Effect/bloodRed.png");
	blue = LoadGraph("resource/Effect/bloodBlue.png");
	yellow = LoadGraph("resource/Effect/bloodYellow.png");
	green = LoadGraph("resource/Effect/bloodGreen.png");
	bloodGraph = LoadGraph("resource/Effect/bloodColor.png");
}

DataSource::~DataSource() {
	DeleteGraph(player);
	DeleteGraph(mapChip);
	DeleteGraph(actionUI);
	DeleteGraph(enemyGraph);
	DeleteGraph(knifeGraph);
	DeleteGraph(slashGraph);
	DeleteGraph(shieldGraph);
	DeleteGraph(red);
	DeleteGraph(blue);
	DeleteGraph(yellow);
	DeleteGraph(green);
	DeleteGraph(bloodGraph);
}
