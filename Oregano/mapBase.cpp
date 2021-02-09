#include "mapBase.h"
#include "constant.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//初期化
MapBase::MapBase() : map_all(AREA_HEIGHT, vector<int>(AREA_WIDTH)) {
	initial_csv = "resource/csv/map_x08y08.csv"; //初期地点のマップ(中央)
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
string MapBase::map_confirmation(const int& cx, const int& cy, string& csv) {
	//if (csv == nullptr) { return; } //nullチェック
	csv.replace(18, 2, csv_num[cx]); //ファイル名のx座標を変更
	csv.replace(21, 2, csv_num[cy]); //ファイル名のy座標を変更
	return csv; //csvファイル名を返す
}

///// <summary>
///// 受け取ったマップデータを上書きする
///// </summary>
///// <param name="map_xy">マップ座標[縦サイズ][横サイズ]</param>
//void MapBase::map_copy(int map_xy[AREA_HEIGHT][AREA_WIDTH]) {
//
//	for (int i = 0; i < AREA_WIDTH; i++) {
//		memcpy(map_xy[i], map_all[i], sizeof(int) * AREA_HEIGHT);
//	}
//}

/// <summary>
/// マップデータのファイル読み込み
/// </summary>
void MapBase::file_import(const int& nx, const int& ny, vector<vector<int>>& map) {

	ifstream file(map_confirmation(nx, ny, initial_csv));
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
		++j;
	}
}
