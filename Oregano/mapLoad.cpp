#include "mapLoad.h"
#include "constant.h"
#include "mapBase.h"

MapBase map;

MapLoad::MapLoad() :
	vecMap(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
	mapAll(81, vector<vector<int>>(AREA_HEIGHT, vector<int>(AREA_WIDTH))) {
}

MapLoad::~MapLoad() {
}

/// <summary>
/// マップデータ配列を読み込み、三次元配列に格納
/// </summary>
void MapLoad::roadMapData() {
	/*  */
	for (int y = 0; y < TOTAL_MAPS_Y; ++y) {
		for (int x = 0; x < TOTAL_MAPS_X; ++x) {
			map.fileImport(x, y, vecMap); //csvファイル読み込み

			mapAll[x + y * TOTAL_MAPS_Y].clear(); //中身を一旦クリア

			for (auto& i : vecMap) //読み込んだ2次元配列データを
				mapAll[x + y * TOTAL_MAPS_Y].push_back(i); //末尾に値を挿入する
		}
	}
}
