#include "map_all.h"
#include "constant_declaration.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int Map_all::map_x = 6400; //x方向
int Map_all::map_y = 6400; //y方向

//初期化
Map_all::Map_all() : map_all(area_height, vector<int>(area_width)) {
	initial_csv = "resource/csv/map_x08y08.csv"; //初期地点のマップ(中央)
	map_width = map_all.at(0).size(); //横のサイズ
	map_height = map_all.size(); //縦のサイズ
	current_map_x = map_x / (block_size * map_width); //現在の全体マップのx座標
	current_map_y = map_y / (block_size * map_height); //現在の全体マップのy座標
	sx = current_map_x - 8;
	sy = current_map_y - 8;
}

Map_all::~Map_all() {
}

/// <summary>
/// 現在の座標を確認し、それに応じたcsvファイルを探す
/// </summary>
/// <param name="cx">現在の全体マップのx座標</param>
/// <param name="cy">現在の全体マップのy座標</param>
/// <param name="csv">csvファイル名</param>
/// <returns>数字を変更したcsvファイル名を返す</returns>
string Map_all::map_confirmation(const int& cx, const int& cy, string& csv) {
	//if (csv == nullptr) { return; } //nullチェック
	csv.replace(18, 2, csv_num[cx]); //ファイル名のx座標を変更
	csv.replace(21, 2, csv_num[cy]); //ファイル名のy座標を変更
	return csv; //csvファイル名を返す
}

///// <summary>
///// 受け取ったマップデータを上書きする
///// </summary>
///// <param name="map_xy">マップ座標[縦サイズ][横サイズ]</param>
//void Map_all::map_copy(int map_xy[area_height][area_width]) {
//
//	for (int i = 0; i < area_width; i++) {
//		memcpy(map_xy[i], map_all[i], sizeof(int) * area_height);
//	}
//}

/// <summary>
/// マップデータのファイル読み込み
/// </summary>
void Map_all::file_import(const int& nx, const int& ny, vector<vector<int>>& map) {

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
