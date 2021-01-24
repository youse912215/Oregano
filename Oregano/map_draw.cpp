#include "map_draw.h"
#include "coordinate_confirmation.h"
#include "map_info.h"
#include "DxLib.h"

Map_draw::Map_draw() : info{_floor, house, shallow, tide, water, stone, woods},
                       map_top_left(area_height, vector<int>(area_width)),
                       map_top_central(area_height, vector<int>(area_width)),
                       map_top_right(area_height, vector<int>(area_width)),
                       map_left_central(area_height, vector<int>(area_width)),
                       map_central(area_height, vector<int>(area_width)),
                       map_right_central(area_height, vector<int>(area_width)),
                       map_bottom_left(area_height, vector<int>(area_width)),
                       map_bottom_central(area_height, vector<int>(area_width)),
                       map_bottom_right(area_height, vector<int>(area_width)) {
}

Map_draw::~Map_draw() {
}

void Map_draw::drawing_current_maps(vector<vector<int>>& map, const int& dir_x, const int& dir_y) {
	file_import(current_map_x + dir_x, current_map_y + dir_y, map); //csvファイル読み込み
	//--- マップチップ描画 ---//
	current_map_drawing(_floor, sx + dir_x, sy + dir_y, map);
	current_map_drawing(house, sx + dir_x, sy + dir_y, map);
	current_map_drawing(shallow, sx + dir_x, sy + dir_y, map);
	current_map_drawing(water, sx + dir_x, sy + dir_y, map);
	current_map_drawing(woods, sx + dir_x, sy + dir_y, map);
	//---------------------//
}

/// <summary>
/// 9マップの描画
/// </summary>
void Map_draw::drawing_map() {
	drawing_current_maps(map_top_left, Left, Top);
	drawing_current_maps(map_top_central, Central, Top);
	drawing_current_maps(map_top_right, Right, Top);
	drawing_current_maps(map_left_central, Left, Central);
	drawing_current_maps(map_central, Central, Central);
	drawing_current_maps(map_right_central, Right, Central);
	drawing_current_maps(map_bottom_left, Left, Bottom);
	drawing_current_maps(map_bottom_central, Central, Bottom);
	drawing_current_maps(map_bottom_right, Right, Bottom);

	DrawFormatString(90, 0, GetColor(255, 255, 255), "(%d, %d)", map_y, map_x, false);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "(%d, %d)", sy, sx, false);
};
