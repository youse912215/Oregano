#pragma once
#include <vector>

using namespace std;

class MapLoad {
private:
	vector<vector<int>> vecMap; //読み込んだマップデータ配列を格納

public:
	vector<vector<vector<int>>> mapAll; //全てのマップデータを格納

	MapLoad();
	~MapLoad();

	void roadMapData(); //マップデータ配列を読み込み、三次元配列に格納
};
