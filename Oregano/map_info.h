#pragma once

//--- �}�b�v�`�b�v���� ---//
enum map_info {
	//��
	_floor,
	//��
	house,
	//��
	shallow,
	//��
	tide,
	//����
	water = 21,
	//��R
	stone = 31,
	//�؁X
	woods = 41,
	//�c��
	h_bridge = 101,
	//����
	w_bridge = 102
};

void map_name(int* column, int* row, const int& map_info);
