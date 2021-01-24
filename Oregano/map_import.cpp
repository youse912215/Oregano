#include "DxLib.h"
#include "map_import.h"
#include "map_info.h"

Map_import::Map_import() {
	map_graph = LoadGraph("resource/map/mapchip32.png"); //マップチップ画像ファイルの読み込み
	column = 0; //列
	row = 0; //行
	screen_x = initial_map_x - map_x; //画面上のx座標
	screen_y = initial_map_y - map_y; //画面上のy座標
	map_between_distance = block_size * area_width; //マップ間距離（800px）
}

Map_import::~Map_import() {
	DeleteGraph(map_graph);
}

//---  現在マップと上下左右斜めの合計9マップを描画　---//

/// <summary>
/// 読み込んだマップに描画する
/// </summary>
/// <param name="map_info"></param>
/// <param name="dis_x">x方向の中心からの距離</param>
/// <param name="dis_y">y方向の中心からの距離</param>
/// <param name="map_xy">マップの配列</param>
void Map_import::current_map_drawing(const int& map_info, const int& dis_x, const int& dis_y,
                                     vector<vector<int>>& map) {

	map_name(&column, &row, map_info); //マップ情報から列と行を取り出す
	//マップの描画
	for (int y = 0; y < map_height; y++) {
		for (int x = 0; x < map_width; x++) {
			//map_infoのチップをdestの位置に描画
			if (map[y][x] == map_info) {
				DrawRectGraph(
					x * block_size + screen_x + map_between_distance * dis_x,
					y * block_size + screen_y + map_between_distance * dis_y,
					column * block_size, row * block_size,
					block_size, block_size,
					map_graph, true, false);
			}
		}
	}
}
