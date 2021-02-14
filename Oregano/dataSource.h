#pragma once

class DataSource {
private:
	int player; //プレイヤー画像の読み込み
	int mapChip; //マップチップ画像ファイルの読み込み

public:
	DataSource();
	~DataSource();

	int playerGraph();
	int mapChipGraph();
};
