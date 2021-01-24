#pragma once
#include "map_all.h"
#include <vector>

using namespace std;

class Map_import : public Map_all {
private:
	int map_graph; //マップチップ画像
	int column; //行番号
	int row; //列番号

public:
	int screen_x; //画面上のx座標
	int screen_y; //画面上のy座標
	int map_between_distance; //マップ間距離（800px）
	Map_import();
	~Map_import();
	void current_map_drawing(const int& map_info, const int& dis_x, const int& dis_y,
	                         vector<vector<int>>& map);
};
