#include "map_info.h"

/// <summary>
/// マップの情報をもとにマップチップ画像の列と行を返す
/// </summary>
/// <param name="column">列</param>
/// <param name="row">行</param>
/// <param name="map_info">マップの情報</param>
void map_name(int* column, int* row, const int& map_info) {
	if (column == nullptr || row == nullptr) { return; } //nullチェック
	switch (map_info) {
	case _floor:
		*column = 0;
		*row = 0;
		break;
	case house:
		*column = 1;
		*row = 0;
		break;
	case shallow:
		*column = 2;
		*row = 0;
		break;
	case water:
		*column = 1;
		*row = 2;
		break;
	case woods:
		*column = 1;
		*row = 4;
		break;
	default:
		break;
	}
}
