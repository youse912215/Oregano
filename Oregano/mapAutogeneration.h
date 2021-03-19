#pragma once
#include "mapBase.h"

class MapAutoGeneration : public MapBase {
private:
	int index; //インデックス

	int autoGenerationMap(const int& random, const int& randomMapNum); //マップの自動生成

	void assigningRandomNum(const int& randomMapNum); //ランダムマップの数字をランダムに割り当て
	void writeFile(const int& x, const int& y, vector<vector<int>>& map); //csvファイルの書き込み

public:
	MapAutoGeneration();
	~MapAutoGeneration();

	vector<vector<int>> roadMap; //読み込んだマップを格納
	vector<vector<vector<int>>> copyMap; //コピーした全マップを格納

	void saveInitMap(const int& x, const int& y); //最初のマップを保存
	void resetFile();
	void writeRandomMap(); //ランダムマップのファイル書き込み	
};
