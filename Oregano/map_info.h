#pragma once

//--- �}�b�v�`�b�v���� ---//
enum map_info {
	//��
	_floor,
	//��
	house,
	//��
	shallow,
	//����
	water = 21,
	//�؁X
	woods = 41
};

void map_name(int* column, int* row, const int& map_info);
