#include "map_draw.h"
#include "coordinate_confirmation.h"
#include "map_info.h"
#include "DxLib.h"

Map_draw::Map_draw() : info{_floor, house, shallow, tide, water, stone, woods} {
}

Map_draw::~Map_draw() {
}


void Map_draw::drawing_top_left() {
	file_import(current_map_x - 1, current_map_y - 1, map_top_left); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(_floor, sx - 1, sy - 1, map_top_left);
	current_map_drawing(house, sx - 1, sy - 1, map_top_left);
	current_map_drawing(shallow, sx - 1, sy - 1, map_top_left);
	current_map_drawing(water, sx - 1, sy - 1, map_top_left);
	current_map_drawing(woods, sx - 1, sy - 1, map_top_left);
	//---------------------//
}

void Map_draw::drawing_top_central() {
	file_import(current_map_x, current_map_y - 1, map_top_central); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(_floor, sx, sy - 1, map_top_central);
	current_map_drawing(house, sx, sy - 1, map_top_central);
	current_map_drawing(shallow, sx, sy - 1, map_top_central);
	current_map_drawing(water, sx, sy - 1, map_top_central);
	current_map_drawing(woods, sx, sy - 1, map_top_central);
	//---------------------//
}

void Map_draw::drawing_top_right() {
	file_import(current_map_x + 1, current_map_y - 1, map_top_right); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(_floor, sx + 1, sy - 1, map_top_right);
	current_map_drawing(house, sx + 1, sy - 1, map_top_right);
	current_map_drawing(shallow, sx + 1, sy - 1, map_top_right);
	current_map_drawing(water, sx + 1, sy - 1, map_top_right);
	current_map_drawing(woods, sx + 1, sy - 1, map_top_right);
	//---------------------//
}

void Map_draw::drawing_left_central() {
	file_import(current_map_x - 1, current_map_y, map_left_central); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(_floor, sx - 1, sy, map_left_central);
	current_map_drawing(house, sx - 1, sy, map_left_central);
	current_map_drawing(shallow, sx - 1, sy, map_left_central);
	current_map_drawing(water, sx - 1, sy, map_left_central);
	current_map_drawing(woods, sx - 1, sy, map_left_central);
	//---------------------//
}

void Map_draw::drawing_central() {
	file_import(current_map_x, current_map_y, map_central); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//

	for (auto i : info) {
		current_map_drawing(i, sx, sy, map_central);
	}
}

void Map_draw::drawing_right_central() {
	file_import(current_map_x + 1, current_map_y, map_right_central); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(_floor, sx + 1, sy, map_right_central);
	current_map_drawing(house, sx + 1, sy, map_right_central);
	current_map_drawing(shallow, sx + 1, sy, map_right_central);
	current_map_drawing(water, sx + 1, sy, map_right_central);
	current_map_drawing(woods, sx + 1, sy, map_right_central);
	//---------------------//
}

void Map_draw::drawing_bottom_left() {
	file_import(current_map_x - 1, current_map_y + 1, map_bottom_left); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(_floor, sx - 1, sy + 1, map_bottom_left);
	current_map_drawing(house, sx - 1, sy + 1, map_bottom_left);
	current_map_drawing(shallow, sx - 1, sy + 1, map_bottom_left);
	current_map_drawing(water, sx - 1, sy + 1, map_bottom_left);
	current_map_drawing(woods, sx - 1, sy + 1, map_bottom_left);
	//---------------------//
}

void Map_draw::drawing_bottom_central() {
	file_import(current_map_x, current_map_y + 1, map_bottom_central); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(_floor, sx, sy + 1, map_bottom_central);
	current_map_drawing(house, sx, sy + 1, map_bottom_central);
	current_map_drawing(shallow, sx, sy + 1, map_bottom_central);
	current_map_drawing(water, sx, sy + 1, map_bottom_central);
	current_map_drawing(woods, sx, sy + 1, map_bottom_central);
	//---------------------//
}

void Map_draw::drawing_bottom_right() {
	file_import(current_map_x + 1, current_map_y + 1, map_bottom_right); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(_floor, sx + 1, sy + 1, map_bottom_right);
	current_map_drawing(house, sx + 1, sy + 1, map_bottom_right);
	current_map_drawing(shallow, sx + 1, sy + 1, map_bottom_right);
	current_map_drawing(water, sx + 1, sy + 1, map_bottom_right);
	current_map_drawing(woods, sx + 1, sy + 1, map_bottom_right);
	//---------------------//
}

/// <summary>
/// 9�}�b�v�̕`��
/// </summary>
void Map_draw::drawing_map() {
	drawing_top_left();
	drawing_top_central();
	drawing_top_right();
	drawing_left_central();
	drawing_central();
	drawing_right_central();
	drawing_bottom_left();
	drawing_bottom_central();
	drawing_bottom_right();


	DrawFormatString(90, 0, GetColor(255, 255, 255), "(%d, %d)", map_y, map_x, false);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "(%d, %d)", sy, sx, false);
};
