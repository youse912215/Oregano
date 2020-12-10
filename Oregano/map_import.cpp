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
}

//---  現在マップと上下左右斜めの合計9マップを描画　---//
/// <summary>
/// 現在マップの描画
/// </summary>
/// <param name="map_info">マップ情報</param>
void Map_import::current_map_drawing(const int& map_info, const int& sign_x, const int& sign_y,
                                     int map_xy[area_height][area_width]) {

	map_name(&column, &row, map_info); //マップ情報から列と行を取り出す
	//マップの描画
	for (int y = 0; y < map_height; y++) {
		for (int x = 0; x < map_width; x++) {
			//map_infoのチップをdestの位置に描画
			if (map_xy[y][x] == map_info) {
				DrawRectGraph(
					x * block_size + screen_x + map_between_distance * sign_x,
					y * block_size + screen_y + map_between_distance * sign_y,
					column * block_size, row * block_size,
					block_size, block_size,
					map_graph, true, false);
			}
		}
	}
}
