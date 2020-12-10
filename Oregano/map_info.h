#pragma once

//--- マップチップ名称 ---//
enum map_info {
	//床
	_floor,
	//家
	house,
	//浅瀬
	shallow,
	//水辺
	water = 21,
	//木々
	woods = 41
};

void map_name(int* column, int* row, const int& map_info);
