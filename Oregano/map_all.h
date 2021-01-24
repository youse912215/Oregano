#pragma once
#include "constant_declaration.h"
#include "input.h"
#include <string>

using namespace std;

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
	int sx;
	int sy;
	void file_import(const int& nx, const int& ny, int map_xy[area_height][area_width]);
	//void map_copy(int map_xy[area_height][area_width]);
	Map_all();
	~Map_all();
};
