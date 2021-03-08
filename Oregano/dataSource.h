#pragma once

class DataSource {
private:

protected:
	int actionUI; //アクションUI画像ファイルの読み込み

public:
	int enemyGraph;
	int player; //プレイヤー画像の読み込み
	int mapChip; //マップチップ画像ファイルの読み込み
	int knifeGraph;
	int slashGraph;
	int shieldGraph;
	int red;
	int blue;
	int green;
	int yellow;
	int blurGraph1;
	int blurGraph2;
	int enemyLife;
	int coinGraph;
	int conditionGraph;
	int passiveGraph;
	int menuGraph;
	int modeGraph;
	int actionGraph;
	int filterGraph1;
	int filterGraph2;
	int shieldGauge;

	DataSource();
	~DataSource();
};
