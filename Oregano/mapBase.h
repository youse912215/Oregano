#pragma once
#include "constant.h"
#include <string>
#include <vector>

using namespace std;

class MapBase {
private:
	const string comma = ","; //カンマ
	const string csvNum[9] = {
			"00", "01", "02", "03", "04", "05", "06", "07", "08",
		}; //csvファイル名を変更するための数字


protected:
	vector<vector<int>> mapBase; //ベースとなるマップ

	string initialCsv; //初期地点のマップ(中央)
	string mapConfirmation(const int& cx, const int& cy, string& csv);

	void fileImport(const int& nx, const int& ny, vector<vector<int>>& map);

public:
	MapBase();
	~MapBase();


};
