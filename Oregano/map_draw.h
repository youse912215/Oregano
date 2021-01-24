#pragma once
#include "map_import.h"
#include <vector>

using namespace std;

class Map_draw : public Map_import {
private:
	vector<int> info;
	vector<vector<int>> map_top_left;
	vector<vector<int>> map_top_central;
	vector<vector<int>> map_top_right;
	vector<vector<int>> map_left_central;
	vector<vector<int>> map_central;
	vector<vector<int>> map_right_central;
	vector<vector<int>> map_bottom_left;
	vector<vector<int>> map_bottom_central;
	vector<vector<int>> map_bottom_right;

	void drawing_current_maps(vector<vector<int>>& map, const int& dir_x, const int& dir_y);
public:
	Map_draw();
	~Map_draw();
	void drawing_map();
};
