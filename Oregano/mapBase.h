#pragma once
#include "constant.h"
#include "inputProcess.h"
#include <string>
#include <vector>

using namespace std;

class MapBase : public Input {
private:
	string initialCsv; //初期地点のマップ(中央)
	const string comma = ","; //カンマ
	const string csvNum[16] = {
			"00", "01", "02", "03", "04", "05", "06", "07",
			"08", "09", "10", "11", "12", "13", "14", "15"
		}; //csvファイル名を変更するための数字
	string mapConfirmation(const int& cx, const int& cy, string& csv);

protected:
	vector<vector<int>> mapBase; //ベースとなるマップ

	void fileImport(const int& nx, const int& ny, vector<vector<int>>& map);
	MapBase();
	~MapBase();

public:

};
