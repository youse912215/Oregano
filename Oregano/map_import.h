#pragma once
#include "map_all.h"

class Map_import : public Map_all {
private:
	int map_graph; //マップチップ画像
	int column; //行番号
	int row; //列番号
	int screen_x; //画面上のx座標
	int screen_y; //画面上のy座標
	int map_between_distance; //マップ間距離（800px）
public:
	Map_import();
	~Map_import();
	void current_map_drawing(const int& map_info, const int& sign_x, const int& sign_y,
	                         int map_xy[area_height][area_width]);
};
