#include "dataSource.h"
#include "DxLib.h"

DataSource::DataSource() {
	/* 画像 */
	player = LoadGraph("resource\\organism\\player.png");
	playerDamage = LoadGraph("resource\\organism\\player2.png");
	mapChip = LoadGraph("resource\\map\\mapchip.png");
	enemyGraph = LoadGraph("resource\\organism\\enemy_1.png");
	knifeGraph = LoadGraph("resource\\organism\\knife.png");
	slashGraph = LoadGraph("resource\\organism\\slash.png");
	shieldGraph = LoadGraph("resource\\organism\\shield.png");
	red = LoadGraph("resource\\Effect\\bloodRed.png");
	blue = LoadGraph("resource\\Effect\\bloodBlue.png");
	yellow = LoadGraph("resource\\Effect\\bloodYellow.png");
	green = LoadGraph("resource\\Effect\\bloodGreen.png");
	blurGraph1 = LoadGraph("resource\\UI\\blur1.png");
	blurGraph2 = LoadGraph("resource\\UI\\blur2.png");
	enemyLife = LoadGraph("resource\\UI\\enemyLife.png");
	coinGraph = LoadGraph("resource\\UI\\coin.png");
	conditionGraph = LoadGraph("resource\\UI\\condition.png");
	passiveGraph = LoadGraph("resource\\UI\\passive.png");
	menuGraph = LoadGraph("resource\\UI\\menu.png");
	actionGraph = LoadGraph("resource\\UI\\action.png");
	filterGraph1 = LoadGraph("resource\\UI\\filter1.png");
	filterGraph2 = LoadGraph("resource\\UI\\filter2.png");
	shieldGauge = LoadGraph("resource\\UI\\shieldGauge.png");
	eventGraph = LoadGraph("resource\\UI\\event.png");
	title = LoadGraph("resource\\Art\\title.png");
	menu = LoadGraph("resource\\Art\\menu.png");
	gameover = LoadGraph("resource\\Art\\gameover.png");
	clear = LoadGraph("resource\\Art\\clear.png");
	event1 = LoadGraph("resource\\Art\\event1.png");
	event2 = LoadGraph("resource\\Art\\event2.png");
	event3 = LoadGraph("resource\\Art\\event3.png");
	titleStart = LoadGraph("resource\\Art\\titleStart.png");
	deviceChange1 = LoadGraph("resource\\Art\\deviceChange.png");
	deviceChange2 = LoadGraph("resource\\Art\\deviceChange2.png");
	gameOverEnd = LoadGraph("resource\\Art\\gameoverEnd.png");

	/* 音 */
	mainBgm = LoadSoundMem("resource\\Music\\bgm.mp3");
	seHit = LoadSoundMem("resource\\Music\\se_hit.mp3");
	seClear = LoadSoundMem("resource\\Music\\se_clear.mp3");
	seDamage = LoadSoundMem("resource\\Music\\se_damage.mp3");
}

/// <summary>
/// ハンドルの削除
/// </summary>
DataSource::~DataSource() {
	/* 画像 */
	DeleteGraph(player);
	DeleteGraph(playerDamage);
	DeleteGraph(mapChip);
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
	DeleteGraph(actionGraph);
	DeleteGraph(filterGraph1);
	DeleteGraph(filterGraph2);
	DeleteGraph(shieldGauge);
	DeleteGraph(eventGraph);
	DeleteGraph(title);
	DeleteGraph(menu);
	DeleteGraph(clear);
	DeleteGraph(gameover);
	DeleteGraph(event1);
	DeleteGraph(event2);
	DeleteGraph(event3);
	DeleteGraph(titleStart);
	DeleteGraph(deviceChange1);
	DeleteGraph(deviceChange2);
	DeleteGraph(gameOverEnd);

	/* 音 */
	DeleteMusicMem(mainBgm);
	DeleteMusicMem(seHit);
	DeleteMusicMem(seClear);
	DeleteMusicMem(seDamage);
}

/// <summary>
/// BGMを流す
/// </summary>
void DataSource::playBgm() {
	PlaySoundMem(mainBgm, DX_PLAYTYPE_LOOP, true);
}

/// <summary>
/// SEを流す
/// </summary>
/// <param name="se">効果音</param>
void DataSource::playSe(const int& se) {
	PlaySoundMem(se, DX_PLAYTYPE_BACK, true);
}
