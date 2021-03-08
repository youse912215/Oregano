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
	red = LoadGraph("resource/Effect/bloodRed.png");
	blue = LoadGraph("resource/Effect/bloodBlue.png");
	yellow = LoadGraph("resource/Effect/bloodYellow.png");
	green = LoadGraph("resource/Effect/bloodGreen.png");
	blurGraph1 = LoadGraph("resource/UI/blur1.png");
	blurGraph2 = LoadGraph("resource/UI/blur2.png");
	enemyLife = LoadGraph("resource/UI/enemyLife.png");
	coinGraph = LoadGraph("resource/UI/coin.png");
	conditionGraph = LoadGraph("resource/UI/condition.png");
	passiveGraph = LoadGraph("resource/UI/passive.png");
	menuGraph = LoadGraph("resource/UI/menu.png");
	modeGraph = LoadGraph("resource/UI/mode.png");
	actionGraph = LoadGraph("resource/UI/action.png");
	filterGraph1 = LoadGraph("resource/UI/filter1.png");
	filterGraph2 = LoadGraph("resource/UI/filter2.png");
	shieldGauge = LoadGraph("resource/UI/shieldGauge.png");
	eventGraph = LoadGraph("resource/UI/event.png");
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
	DeleteGraph(blurGraph1);
	DeleteGraph(blurGraph2);
	DeleteGraph(enemyLife);
	DeleteGraph(coinGraph);
	DeleteGraph(conditionGraph);
	DeleteGraph(passiveGraph);
	DeleteGraph(menuGraph);
	DeleteGraph(modeGraph);
	DeleteGraph(actionGraph);
	DeleteGraph(filterGraph1);
	DeleteGraph(filterGraph2);
	DeleteGraph(shieldGauge);
	DeleteGraph(eventGraph);
}
