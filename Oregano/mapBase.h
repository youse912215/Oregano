#pragma once
#include "constant.h"
#include <string>
#include <vector>

using namespace std;

class MapBase {
private:
	const string comma = ","; //カンマ
	const string csvNum[TOTAL_MAPS_X] = {
			"00", "01", "02", "03", "04", "05", "06", "07", "08",
		}; //csvファイル名を変更するための数字


protected:
	string initialCsv; //初期地点のマップ(中央)
	string mapConfirmation(const int& cx, const int& cy, string& csv); //現在のマップ座標によって、csvファイルを変更

public:
	MapBase();
	~MapBase();

	void fileImport(const int& nx, const int& ny, vector<vector<int>>& map); //マップデータの読み込み
};
