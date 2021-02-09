#include "mapInformation.h"
#include "constant.h"

/// <summary>
/// マップの情報をもとにマップチップ画像の列と行を返す
/// </summary>
/// <param name="column">列</param>
/// <param name="row">行</param>
/// <param name="map_info">マップの情報</param>
void mapName(int* column, int* row, const int& map_info) {
	if (column == nullptr || row == nullptr) { return; } //nullチェック
	switch (map_info) {
	case FLOOR:
		*column = 0;
		*row = 0;
		break;
	case HOUSE:
		*column = 1;
		*row = 0;
		break;
	case SHALLOW:
		*column = 2;
		*row = 0;
		break;
	case TIDE:
		*column = 3;
		*row = 0;
		break;
	case WATER:
		*column = 1;
		*row = 2;
		break;
	case STONE:
		*column = 1;
		*row = 3;
		break;
	case WOODS:
		*column = 1;
		*row = 4;
		break;
	default:
		break;
	}
}
