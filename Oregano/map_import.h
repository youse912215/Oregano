#pragma once
#include "map_all.h"

class Map_import : public Map_all {
private:
	int map_graph; //�}�b�v�`�b�v�摜
	int column; //�s�ԍ�
	int row; //��ԍ�

public:
	int screen_x; //��ʏ��x���W
	int screen_y; //��ʏ��y���W
	int map_between_distance; //�}�b�v�ԋ����i800px�j
	Map_import();
	~Map_import();
	void current_map_drawing(const int& map_info, const int& dis_x, const int& dis_y,
	                         int map_xy[area_height][area_width]);
};
