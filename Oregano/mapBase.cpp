#include "mapBase.h"
#include "constant.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//初期化
MapBase::MapBase() :
	mapBase(AREA_HEIGHT, vector<int>(AREA_WIDTH)) {
	initialCsv = "resource/csv/map_x08y08.csv"; //初期地点のマップ(中央)
}

MapBase::~MapBase() {
}

/// <summary>
/// 現在の座標を確認し、それに応じたcsvファイルを探す
/// </summary>
/// <param name="cx">現在の全体マップのx座標</param>
/// <param name="cy">現在の全体マップのy座標</param>
/// <param name="csv">csvファイル名</param>
/// <returns>数字を変更したcsvファイル名を返す</returns>
string MapBase::mapConfirmation(const int& cx, const int& cy, string& csv) {
	//if (csv == nullptr) { return; } //nullチェック
	csv.replace(18, 2, csvNum[cx]); //ファイル名のx座標を変更
	csv.replace(21, 2, csvNum[cy]); //ファイル名のy座標を変更
	return csv; //csvファイル名を返す
}

/// <summary>
/// マップデータのファイル読み込み
/// </summary>
void MapBase::fileImport(const int& nx, const int& ny, vector<vector<int>>& map) {

	ifstream file(mapConfirmation(nx, ny, initialCsv));
	string line;
	int j = 0;
	while (getline(file, line)) {
		int i = 0;
		// カンマを区切り文字として切り分け、intに変換してdata[][]に格納する
		for (string::size_type spos, epos = 0;
		     (spos = line.find_first_not_of(comma, epos)) != string::npos;) {
			string token = line.substr(spos, (epos = line.find_first_of(comma, spos)) - spos);
			map[j][i++] = stoi(token);
		}
		++j; //加算
	}
}
