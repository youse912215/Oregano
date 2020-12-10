#include "DxLib.h"
#include "map_import.h"
#include "map_info.h"

Map_import::Map_import() {
	map_graph = LoadGraph("resource/map/mapchip32.png"); //�}�b�v�`�b�v�摜�t�@�C���̓ǂݍ���
	column = 0; //��
	row = 0; //�s
	screen_x = initial_map_x - map_x; //��ʏ��x���W
	screen_y = initial_map_y - map_y; //��ʏ��y���W
	map_between_distance = block_size * area_width; //�}�b�v�ԋ����i800px�j
}

Map_import::~Map_import() {
}

//---  ���݃}�b�v�Ə㉺���E�΂߂̍��v9�}�b�v��`��@---//
/// <summary>
/// ���݃}�b�v�̕`��
/// </summary>
/// <param name="map_info">�}�b�v���</param>
void Map_import::current_map_drawing(const int& map_info, const int& sign_x, const int& sign_y,
                                     int map_xy[area_height][area_width]) {

	map_name(&column, &row, map_info); //�}�b�v��񂩂��ƍs�����o��
	//�}�b�v�̕`��
	for (int y = 0; y < map_height; y++) {
		for (int x = 0; x < map_width; x++) {
			//map_info�̃`�b�v��dest�̈ʒu�ɕ`��
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
