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
