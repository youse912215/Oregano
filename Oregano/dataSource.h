#pragma once

class DataSource {
private:

	//int actionUI; //アクションUI画像ファイルの読み込み

protected:
	int actionUI; //アクションUI画像ファイルの読み込

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

	DataSource();
	~DataSource();
};
