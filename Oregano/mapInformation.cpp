#include "mapInformation.h"
#include "constant.h"

/// <summary>
/// �}�b�v�̏������ƂɃ}�b�v�`�b�v�摜�̗�ƍs��Ԃ�
/// </summary>
/// <param name="column">��</param>
/// <param name="row">�s</param>
/// <param name="map_info">�}�b�v�̏��</param>
void mapName(int* column, int* row, const int& map_info) {
	if (column == nullptr || row == nullptr) { return; } //null�`�F�b�N
	switch (map_info) {
	case FLOOR:
		*column = 0;
		*row = 0;
		break;
	case BEACH:
		*column = 1;
		*row = 0;
		break;
	case BRIDGE_WIDTH:
		*column = 2;
		*row = 2;
		break;
	case BRIDGE_HEIGHT:
		*column = 3;
		*row = 2;
		break;
	case FLOWER:
		*column = 0;
		*row = 1;
		break;
	case MUSHROOM:
		*column = 0;
		*row = 2;
		break;
	case HOUSE:
		*column = 1;
		*row = 1;
		break;
	case SHALLOW:
		*column = 2;
		*row = 0;
		break;
	case TIDE:
		*column = 3;
		*row = 0;
		break;
	case CRYSTAL:
		*column = 4;
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
	case MINERAL:
		*column = 2;
		*row = 3;
		break;
	case WOODS:
		*column = 1;
		*row = 4;
		break;
	case TREASURE_BOX:
		*column = 0;
		*row = 3;
		break;
	default:
		break;
	}
}
