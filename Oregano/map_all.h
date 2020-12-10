#pragma once
#include "constant_declaration.h"
#include "input.h"
#include <string>

using namespace std;

//--- マップの各方向の宣言 ---//
//extern int map_x;
//extern int map_y;

//extern int whole_map_position_x; //x方向における中心からの距離
//extern int whole_map_position_y; //y方向における中心からの距離

class Map_all : public Input {
private:
	string initial_csv; //初期地点のマップ(中央)
	const string comma = ","; //カンマ
	const string csv_num[16] = {
			"00", "01", "02", "03", "04", "05", "06", "07",
			"08", "09", "10", "11", "12", "13", "14", "15"
		}; //csvファイル名を変更するための数字
	string map_confirmation(const int& cx, const int& cy, string& csv);
public:
	static int map_x;
	static int map_y;
	int map_all[area_height][area_width];
	bool map_data[16][16];
	int current_map_x;
	int current_map_y;
	int map_width; //1マップあたりの配列の横サイズ
	int map_height; //1マップあたりの配列の縦サイズ]
	void get_map_data(const int& cx, const int& cy);
	void file_import(int map_xy[area_height][area_width]);
	void map_copy(int map_xy[area_height][area_width]);
	Map_all();
	~Map_all();
};
