#pragma once
#include "mapBase.h"

class MapAutogeneration : public MapBase {
private:
	vector<vector<int>> roadMap; //読み込んだマップを格納


	int autogenerationMap(const int& random, const int& randomMapNum); //マップの自動生成

	void AssigningRandomNum(const int& randomMapNum); //ランダムマップの数字をランダムに割り当て
	void fileWrite(const int& x, const int& y); //csvファイルの書き込み

public:
	MapAutogeneration();
	~MapAutogeneration();

	void writeRandomMap(); //ランダムマップのファイル書き込み	
};
