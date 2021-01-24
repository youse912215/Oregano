#pragma once

//--- マップチップ名称 ---//
enum map_info {
	//床
	_floor,
	//家
	house,
	//浅瀬
	shallow,
	//潮
	tide,
	//水辺
	water = 21,
	//岩山
	stone = 31,
	//木々
	woods = 41,
	//縦橋
	h_bridge = 101,
	//横橋
	w_bridge = 102
};

void map_name(int* column, int* row, const int& map_info);
